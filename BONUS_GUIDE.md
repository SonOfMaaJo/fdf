# Guide d'Implémentation des Bonus FdF

Ce guide récapitule les étapes pour implémenter les transformations bonus (Changement de projection, Cisaillement, Rotations, Zoom, etc.) de manière structurée et performante.

---

## 1. Mise à jour de la Structure `t_map` (Header)

Ajoute les champs nécessaires pour stocker l'état de tes transformations.

```c
typedef struct s_map
{
    // ... champs existants (width, height, dots, limits) ...

    // --- TRANSFORMATIONS ---
    int         zoom;           // Facteur de zoom global
    float       offset_x;       // Décalage horizontal (Translation)
    float       offset_y;       // Décalage vertical (Translation)
    double      z_divisor;      // Aplatissement du relief (diviseur d'altitude)
    
    // --- ROTATIONS (Angles en radians) ---
    double      angle_x;        // Rotation autour de X (Pitch)
    double      angle_y;        // Rotation autour de Y (Yaw)
    double      angle_z;        // Rotation autour de Z (Roll)

    // --- BONUS SPÉCIFIQUES ---
    int         projection_type; // 0 = ISO, 1 = PARALLEL (Vue de dessus)
    double      shear_factor;    // Facteur de cisaillement (ex: penche l'axe X selon Y)
}   t_map;
```

---

## 2. Le Pipeline de Transformation (Logique)

L'ordre des opérations est **CRUCIAL**. Tout doit se passer dans une fonction unique (ex: `project_point`) appelée pour chaque point de la grille avant de dessiner.

**Ordre Canonique :**
1.  **Copie** des coordonnées originales (`i, j, z`).
2.  **Modification Z** (Altitude).
3.  **Cisaillement** (Déformation géométrique).
4.  **Rotations 3D** (Tourner le monde).
5.  **Projection** (Passer de 3D à 2D : Iso ou Parallèle).
6.  **Zoom** (Agrandir le résultat 2D).
7.  **Offset** (Centrer sur l'écran).

### Code "Maitre" suggéré pour `srcs/maths_transformations.c`

```c
void transform_and_project(t_dot dot, t_map *map, int *final_x, int *final_y)
{
    double x = dot.abscissa;
    double y = dot.ordinate;
    double z = dot.altitude;

    // 1. Aplatissement Z
    z /= map->z_divisor;

    // 2. Cisaillement (Bonus transformation extra)
    // "Penche" la grille vers la droite en fonction de la ligne
    x += y * map->shear_factor;

    // 3. Rotations (Bonus rotation)
    rotate_x(&y, &z, map->angle_x);
    rotate_y(&x, &z, map->angle_y);
    rotate_z(&x, &y, map->angle_z);

    // 4. Choix de Projection (Bonus projection)
    double proj_x, proj_y;
    
    if (map->projection_type == 0) // ISO
    {
        proj_x = (x - y) * cos(0.523599);
        proj_y = -z + (x + y) * sin(0.523599);
    }
    else // PARALLEL (Orthographique / Vue de dessus)
    {
        proj_x = x;
        proj_y = y;
    }

    // 5. Zoom et Offset (Basique)
    *final_x = (int)((proj_x * map->zoom) + map->offset_x);
    *final_y = (int)((proj_y * map->zoom) + map->offset_y);
}
```

---

## 3. Contrôles Clavier (Hooks)

Voici les touches recommandées et leurs codes (Linux/MiniLibX).

### A. Gestion Fenêtre
| Action | Touche | Keycode | Code C |
| :--- | :--- | :--- | :--- |
| **Quitter** | `ESC` | `65307` | `close_program(vars)` |
| **Reset** | `R` | `114` | Remet toutes les valeurs de `map` à défaut. |

### B. Mouvements & Zoom
| Action | Touche | Keycode | Action sur `t_map` |
| :--- | :--- | :--- | :--- |
| **Haut** | `↑` | `65362` | `offset_y -= 10` |
| **Bas** | `↓` | `65364` | `offset_y += 10` |
| **Gauche** | `←` | `65361` | `offset_x -= 10` |
| **Droite** | `→` | `65363` | `offset_x += 10` |
| **Zoom +** | `+` (Pavé) | `65451` | `zoom += 1` |
| **Zoom -** | `-` (Pavé) | `65453` | `if (zoom > 1) zoom -= 1` |

### C. Rotations (Bonus)
| Action | Touche | Keycode | Action sur `t_map` |
| :--- | :--- | :--- | :--- |
| **X (Pitch)** | `W` / `S` | `119` / `115` | `angle_x += 0.05` / `-= 0.05` |
| **Y (Yaw)** | `A` / `D` | `97` / `100` | `angle_y += 0.05` / `-= 0.05` |
| **Z (Roll)** | `Q` / `E` | `113` / `101` | `angle_z += 0.05` / `-= 0.05` |

### D. Transformations Spéciales (Bonus)
| Action | Touche | Keycode | Action sur `t_map` |
| :--- | :--- | :--- | :--- |
| **Projection ISO** | `I` | `105` | `projection_type = 0` |
| **Projection //** | `P` | `112` | `projection_type = 1` |
| **Relief +** | `PageUp` | `65365` | `if (z_divisor > 0.1) z_divisor -= 0.1` |
| **Relief -** | `PageDown`| `65366` | `z_divisor += 0.1` |
| **Shear +** | `K` | `107` | `shear_factor += 0.1` |
| **Shear -** | `L` | `108` | `shear_factor -= 0.1` |

---

## 4. Implémentation du Hook

Dans `main.c` ou `events.c` :

1.  Créer une fonction `int key_handler(int key, void *param)`.
2.  Caster `param` en `t_vars *` (ta struct globale qui contient `mlx`, `win`, `img`, `map`).
3.  Faire un grand `if / else if` pour vérifier `key`.
4.  Modifier la valeur correspondante dans `map`.
5.  **IMPORTANT :** À la fin de la fonction, si une touche a été pressée :
    *   `mlx_destroy_image` (Détruire l'ancienne image).
    *   `mlx_new_image` (Créer une nouvelle noire).
    *   `fill_img_with_pixel_dots` (Redessiner avec les nouvelles valeurs).
    *   `mlx_put_image_to_window` (Afficher).

Bon code !
