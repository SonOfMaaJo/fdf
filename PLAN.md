# Plan d'Action - Projet FdF (Fil de Fer)

Ce document détaille les étapes de réalisation du projet FdF, complété par les concepts techniques clés à maîtriser.

---

## 💡 Concepts Fondamentaux à Comprendre

### 1. La Réalité du Pixel
L'écran n'est pas une surface de dessin continue, mais une grille de points lumineux. Dessiner une ligne consiste à déterminer quels carreaux de cette grille doivent être "allumés".

### 2. Le Pixel Buffer (La Performance)
L'utilisation de `mlx_pixel_put` est interdite pour un rendu fluide car elle communique avec le serveur graphique pour chaque point. La solution est de créer un **buffer** (une zone tampon en RAM) :
- C'est un tableau de type `char *` où vous écrivez directement.
- Un pixel occupe généralement **4 octets** (32 bits).
- L'ordre des couleurs est souvent **B|G|R|A** (Blue, Green, Red, Alpha).

**La Formule de l'Index :**
Pour trouver l'emplacement exact d'un pixel $(x, y)$ dans le buffer, on utilise :
`index = (y * size_line) + (x * (bits_per_pixel / 8))`
*Où `size_line` est le nombre d'octets par ligne (donné par la MLX).*

### 3. La Projection Isométrique
Le fichier `.fdf` contient des points en 3D $(x, y, z)$. L'écran est en 2D $(x, y)$. La projection isométrique permet de simuler la 3D sur un plan 2D en inclinant les axes.

**Formules classiques :**
- $x\_final = (x - y) * \cos(30^\circ)$
- $y\_final = (x + y) * \sin(30^\circ) - z$

---

## 🛠️ Étapes de Développement

## Phase 1 : Architecture et En-têtes (`fdf.h`)
- **Tâche** : Concevoir les structures `t_dot`, `t_img`, `t_map` et la structure globale `t_fdf`.
- **Focus** : Organisation des données pour éviter de passer trop d'arguments aux fonctions.

## Phase 2 : Le Parsing (Lecture de la carte)
- **Tâche** : Transformer le fichier texte en tableau de `t_dot`.
- **Focus** : Utilisation de `get_next_line`, `ft_split` et gestion rigoureuse des allocations (`malloc`).

## Phase 3 : Le Moteur de Rendu (Mathématiques)
- **Tâche** : Implémenter l'algorithme de **Bresenham**.
- **Étude** : Comprendre comment tracer un segment de $(x1, y1)$ à $(x2, y2)$ en utilisant uniquement des additions et soustractions d'entiers (plus rapide que les flottants).

## Phase 4 : L'Image Buffer (Implémentation)
- **Tâche** : Créer la fonction `my_mlx_pixel_put`.
- **Focus** : Écriture directe dans la mémoire (`char *addr`) en respectant l'endianness et le `line_length`.

## Phase 5 : Gestion des Événements (Interactivité)
- **Tâche** : Gérer la fermeture (Échap / Croix rouge) et les touches clavier.
- **Étude** : Les prototypes des fonctions de "hook" de la MiniLibX.

## Phase 6 : Les Bonus (Transformation)
- **Tâche** : Ajouter le zoom, la rotation (matrices) et la translation (offset).
- **Étude** : Comment modifier les variables globales de vue avant de redessiner l'image.

## Phase 7 : Nettoyage et Optimisation
- **Tâche** : Passer le projet à `Valgrind` et s'assurer que le rendu est instantané.