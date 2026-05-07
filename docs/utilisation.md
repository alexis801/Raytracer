# Comment utiliser le Raytracer

## Compiler le programme

Tapez cette commande dans le terminal :

```
make
```

Ca cree le programme `raytracer`.

## Lancer le programme

Le programme prend un fichier de scene et genere une image.

```
./raytracer scenes/sujet.cfg > image.ppm
```

L'image est au format PPM. Pour la voir, ouvrez-la avec un viewer d'images :

```
xdg-open image.ppm
```

## Ecrire un fichier de scene

Le fichier de scene decrit ce que le programme doit dessiner. Il a trois parties : la camera, les formes et les lumieres.

### La camera

La camera c'est le point de vue. On choisit ou elle est, dans quelle direction elle regarde et la taille de l'image.

```cfg
camera:
{
    resolution = { width = 800; height = 600; };
    position = { x = 0.0; y = -100.0; z = 20.0; };
    rotation = { x = -90.0; y = 0.0; z = 0.0; };
    fieldOfView = 72.0;
};
```

- `resolution` : la taille de l'image en pixels
- `position` : ou se trouve la camera dans la scene
- `rotation` : dans quelle direction elle regarde
- `fieldOfView` : l'angle de vue en degres (plus c'est grand, plus on voit large)

### Les formes

Les formes sont les objets qui apparaissent dans l'image. Chaque forme a un type, une position et une couleur.

**Sphere** (une boule) :
```cfg
{ type = "sphere"; x = 0.0; y = 0.0; z = 5.0; r = 2.0;
  color = { r = 255; g = 0; b = 0; }; }
```
- `x, y, z` : position du centre
- `r` : taille de la sphere
- `color` : couleur en rouge, vert, bleu (de 0 a 255)

**Plan** (une surface plate infinie) :
```cfg
{ type = "plane"; axis = "Z"; position = 0.0;
  color = { r = 200; g = 200; b = 200; }; }
```
- `axis` : dans quelle direction le plan est oriente (X, Y ou Z)
- `position` : ou se trouve le plan sur cet axe

**Cone** (une forme pointue) :
```cfg
{ type = "cone"; axis = "Y"; x = 0.0; y = 0.0; z = 0.0;
  angle = 30.0; color = { r = 0; g = 255; b = 0; }; }
```
- `axis` : axe du cone
- `x, y, z` : position de la pointe
- `angle` : ouverture du cone en degres

**Cylindre** (un tube) :
```cfg
{ type = "cylinder"; x = 0.0; y = 0.0; z = 0.0; r = 2.0;
  color = { r = 0; g = 0; b = 255; }; }
```
- `x, y, z` : position du centre
- `r` : taille du cylindre

### Les materiaux

On peut changer le comportement d'une forme face a la lumiere. Ces parametres sont optionnels.

```cfg
{ type = "sphere"; x = 0.0; y = 0.0; z = 5.0; r = 2.0;
  color = { r = 255; g = 255; b = 255; };
  reflection = 0.1; transparency = 0.9; refraction = 1.5; }
```

- `reflection` : a quel point la forme reflete ce qui l'entoure. 0 = pas de reflet, 1 = miroir pur.
- `transparency` : a quel point on voit a travers la forme. 0 = opaque, 1 = totalement transparent.
- `refraction` : comment la lumiere se courbe en traversant la forme. 1.0 = air, 1.5 = verre, 2.4 = diamant.

### Les groupes

On peut regrouper des formes ensemble. Si on deplace le groupe, tout bouge ensemble.

```cfg
{
    type = "group";
    objects = (
        { type = "sphere"; x = 0.0; y = 0.0; z = 0.0; r = 1.0;
          color = { r = 255; g = 0; b = 0; }; },
        { type = "sphere"; x = 3.0; y = 0.0; z = 0.0; r = 1.0;
          color = { r = 0; g = 255; b = 0; }; }
    );
}
```

On peut aussi mettre des groupes dans des groupes.

### Les lumieres

Les lumieres eclairent la scene. Sans lumiere, tout est noir.

```cfg
lights:
{
    ambient = 0.3;
    diffuse = 0.7;
    point = (
        { x = 100.0; y = -50.0; z = 200.0; }
    );
    directional = (
        { x = 0.0; y = -1.0; z = 0.0; }
    );
};
```

- `ambient` : lumiere de base qui eclaire partout pareil. Entre 0 et 1.
- `diffuse` : force de la lumiere sur les surfaces. Entre 0 et 1.
- `point` : lumiere qui vient d'un point precis (comme une ampoule).
- `directional` : lumiere qui vient d'une direction (comme le soleil).

## Exemple complet

```cfg
camera:
{
    resolution = { width = 640; height = 480; };
    position = { x = 0.0; y = -100.0; z = 20.0; };
    rotation = { x = -90.0; y = 0.0; z = 0.0; };
    fieldOfView = 72.0;
};

primitives:
{
    objects = (
        { type = "sphere"; x = 0.0; y = 5.0; z = 20.0; r = 20.0;
          color = { r = 255; g = 255; b = 255; };
          reflection = 0.8; },
        { type = "plane"; axis = "Z"; position = 0.0;
          color = { r = 200; g = 200; b = 200; }; }
    );
};

lights:
{
    ambient = 0.3;
    diffuse = 0.7;
    point = (
        { x = 100.0; y = -50.0; z = 200.0; }
    );
    directional = ();
};
```

Cette scene dessine une sphere miroir posee sur un plan gris, eclairee par une lumiere ponctuelle.

## Glossaire

- **Raytracer** : programme qui dessine des images en simulant des rayons de lumiere.
- **PPM** : format d'image simple. Le fichier contient les couleurs de chaque pixel en texte.
- **CFG** : fichier de configuration qui decrit la scene (formes, lumieres, camera). Il utilise le format libconfig.
- **libconfig** : bibliotheque qui permet de lire les fichiers de configuration `.cfg`.
- **xdg-open** : commande Linux qui ouvre un fichier avec le programme par defaut (viewer d'images pour un `.ppm`).
- **Pixel** : un point de l'image.
- **Rayon** : une ligne droite lancee depuis la camera vers la scene.
- **Normale** : direction perpendiculaire a la surface d'un objet. Elle sert a calculer comment la lumiere rebondit.
- **Reflexion** : quand la lumiere rebondit sur un objet, comme un miroir.
- **Refraction** : quand la lumiere se courbe en passant a travers un objet transparent, comme du verre.
- **Anti-aliasing** : technique pour lisser les bords des objets. Sans ca, les bords sont en escalier.
- **Multithreading** : utiliser plusieurs coeurs du processeur en meme temps pour que le rendu soit plus rapide.
- **Composite** : design pattern qui permet de regrouper des objets ensemble. Un groupe se comporte comme un seul objet.
- **Factory** : design pattern qui permet de creer des objets a partir de leur nom (par exemple "sphere" cree une Sphere).
- **Ombre portee** : quand un objet bloque la lumiere, il fait de l'ombre sur les objets derriere lui.
