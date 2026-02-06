# Gestion des Événements avec la MiniLibX (Clavier & Souris)

Pour rendre ton projet **FdF** interactif, tu dois capturer les entrées utilisateur. La MiniLibX utilise un système de "hooks" (crochets) qui appellent une fonction spécifique dès qu'un événement survient.

## 1. Les Hooks de base (`mlx_hook`)

La fonction la plus polyvalente est `mlx_hook`. Elle permet de s'abonner à n'importe quel événement X11.

```c
int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*f)(), void *param);
```

### Événements Communs (X11)
- `2` : **KeyPress** (Touche pressée)
- `3` : **KeyRelease** (Touche relâchée)
- `4` : **ButtonPress** (Clic souris / Molette)
- `5` : **ButtonRelease** (Bouton relâché)
- `6` : **MotionNotify** (Mouvement de la souris)
- `17` : **DestroyNotify** (Clic sur la croix rouge de la fenêtre)

---

## 2. Gestion du Clavier

La MiniLibX propose une version simplifiée pour le clavier : `mlx_key_hook`. Cependant, pour gérer l'appui prolongé ou des comportements complexes, on utilise souvent `mlx_hook` avec l'événement `2`.

### Exemple de code :
```c
#define KEY_ESC 65307
#define KEY_W 119

int	handle_keypress(int keysym, void *param)
{
	if (keysym == KEY_ESC)
		exit_program(param); // Ta fonction pour fermer proprement
	if (keysym == KEY_W)
		printf("La touche W a été pressée
");
	return (0);
}

// Dans ton main ou ton init :
mlx_hook(win_ptr, 2, 1L<<0, handle_keypress, &data);
```

---

## 3. Gestion de la Souris

La souris gère à la fois les clics et la molette (utile pour le **Zoom** dans FdF).

### Codes des boutons :
- `1` : Clic gauche
- `2` : Clic milieu
- `3` : Clic droit
- `4` : Molette haut (Zoom +)
- `5` : Molette bas (Zoom -)

### Exemple de code :
```c
int	handle_mouse(int button, int x, int y, void *param)
{
	t_data *data = (t_data *)param;

	if (button == 4) // Zoom in
		data->map.zoom += 2;
	else if (button == 5) // Zoom out
		data->map.zoom -= 2;
	
	render_map(data); // Redessiner la map après le changement
	return (0);
}

// Dans ton initialisation :
mlx_hook(win_ptr, 4, 1L<<2, handle_mouse, &data);
```

---

## 4. Fermeture de la fenêtre (La Croix Rouge)

C'est une exigence courante à 42 : cliquer sur la croix de la fenêtre doit fermer le programme proprement (sans fuite de mémoire).

```c
int	close_window(void *param)
{
	// Appelle tes fonctions de free ici
	exit(0);
	return (0);
}

// Dans ton initialisation :
mlx_hook(win_ptr, 17, 0, close_window, &data);
```

---

## 5. La Boucle Infinie (`mlx_loop`)

Pour que tes hooks fonctionnent, ton programme doit rester "en écoute". C'est le rôle de `mlx_loop`.

```c
int main()
{
    // ... init mlx, win, img ...
    mlx_hook(win, 2, 1L<<0, handle_keypress, &data);
    mlx_hook(win, 17, 0, close_window, &data);
    
    mlx_loop(mlx_ptr); // Le programme s'arrête ici et attend les événements
    return (0);
}
```

## 6. Prototypes et Paramètres des Handlers

Les fonctions que vous passez aux hooks doivent respecter des signatures strictes. Voici le détail de chaque paramètre.

### A. Clavier (KeyPress / KeyRelease)
**Prototype :** `int function(int keysym, void *param);`
- **`keysym`** : Le code numérique de la touche pressée (ex: `65307` pour ESC). Ces codes dépendent de votre système (X11 sous Linux).
- **`param`** : Le pointeur générique que vous avez passé lors de l'appel au hook (généralement votre structure principale).

### B. Souris - Clics & Molette (ButtonPress / ButtonRelease)
**Prototype :** `int function(int button, int x, int y, void *param);`
- **`button`** : Le numéro du bouton utilisé (1: Gauche, 2: Milieu, 3: Droit, 4: Molette Haut, 5: Molette Bas).
- **`x`** : La position horizontale du curseur dans la fenêtre au moment du clic.
- **`y`** : La position verticale du curseur dans la fenêtre au moment du clic.
- **`param`** : Votre structure de données.

### C. Souris - Mouvement (MotionNotify)
**Prototype :** `int function(int x, int y, void *param);`
- **`x`** : Nouvelle position horizontale de la souris.
- **`y`** : Nouvelle position verticale de la souris.
- **`param`** : Votre structure de données.

### D. Événements de Fenêtre (Destruction / Expose)
**Prototype :** `int function(void *param);`
- **`param`** : Votre structure de données. C'est l'unique moyen de récupérer vos pointeurs pour libérer la mémoire lors de la fermeture (croix rouge).

---

### Pourquoi respecter ces prototypes ?
La MiniLibX est écrite en C mais interagit avec le serveur graphique. Lorsqu'un événement survient, le serveur "pousse" un nombre précis d'arguments dans la pile d'exécution. Si votre fonction n'en attend pas assez ou en attend trop, elle lira des données corrompues ou provoquera un **Segmentation Fault**.
