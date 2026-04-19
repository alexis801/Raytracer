# Cahier des Charges - Raytracer

## Le projet

On doit faire un programme qui genere des images 3D. On lui donne un fichier qui decrit une scene et il produit une image. Le programme simule des rayons de lumiere pour calculer la couleur de chaque pixel.

On est 4 sur le projet. C'est dans le cadre du module OOP, en C++.

---

## Ce qu'on doit faire

### Obligatoire

On doit pouvoir afficher des spheres et des plans. Les spheres c'est des boules, les plans c'est des surfaces plates comme un sol.

On doit pouvoir deplacer les objets dans la scene avec la translation.

Il faut deux types de lumieres. La lumiere ambiante eclaire tout pareil partout. La lumiere directionnelle vient d'une direction, comme le soleil.

Chaque objet a une couleur.

La scene est decrite dans un fichier .cfg qu'on parse avec libconfig++. Ce fichier contient la camera, les objets et les lumieres.

L'image sort en format PPM sur stdout.

### Recommande

Une fois que le reste marche, on ajoute le cylindre et le cone. On ajoute la rotation pour tourner les objets. On ajoute les ombres.

### Bonus

On peut ajouter plein de trucs en plus pour avoir des points bonus. Des nouvelles formes comme le tore ou les triangles. Des materiaux comme la reflexion, la transparence ou les textures. Des optimisations comme le multithreading. Une interface graphique avec SFML. Chaque bonus rapporte entre 0.5 et 3 points.

---

## Contraintes

Le projet se compile avec make. Le binaire s'appelle raytracer. Les plugins vont dans ./plugins/.

On a le droit d'utiliser la stdlib C/C++, libconfig++ et SFML. Rien d'autre sans demander aux profs.

On doit utiliser des interfaces pour les primitives et les lumieres. On doit utiliser au moins 2 design patterns parmi Factory, Builder, Composite, Decorator, Observer, State et Mediator.

En cas d'erreur le programme affiche un message sur stderr et retourne 84. Sinon il retourne 0.

---

## Comment ca marche

On lance le programme avec `./raytracer scene.cfg`. L'image PPM sort sur stdout, on peut la rediriger dans un fichier avec `./raytracer scene.cfg > image.ppm`.

Le fichier de scene a 3 parties : camera (position, rotation, resolution, fov), primitives (les objets) et lights (les lumieres).

---

## Planning

Phase 1 : on met en place le projet, les interfaces, le moteur de rendu et la sortie PPM.

Phase 2 : on fait la sphere, le plan, les lumieres, la translation, la couleur et le parser.

Phase 3 : on ajoute le cylindre, le cone, la rotation et les ombres.

Phase 4 : on fait les bonus et on prepare les scenes de demo pour la soutenance.
