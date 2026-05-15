# Raytracer

Programme qui genere des images realistes en simulant le comportement de la lumiere.

## Build

Pour compiler le projet, utilisez la commande `make` dans le terminal.

## Usage

Pour lancer le programme, utilisez la commande `./raytracer` suivie du chemin vers un fichier de scene.

Exemple: `./raytracer scenes/sujet.cfg > output.ppm`

## Primitives disponibles

- Sphere
- Plan
- Cylindre (infini ou avec une hauteur)
- Cone (infini ou avec une hauteur)
- Triangle

## Lumieres disponibles

- Ambiante
- Directionnelle (avec couleur)
- Ponctuelle (avec couleur)

## Transformations disponibles

- Translation
- Rotation

## Materiaux

Chaque objet peut avoir :

- Une couleur unie
- De la reflexion (effet miroir)
- De la transparence et de la refraction (effet verre)
- Des reflets brillants (modele de Phong : specular et shininess)

## Fonctionnalites bonus

- **Plusieurs lumieres** ponctuelles ou directionnelles dans une meme scene
- **Lumieres colorees** (rouge, bleu, vert, etc.)
- **Anti-aliasing** par super-sampling pour des bords lisses
- **Multithreading** pour accelerer le rendu
- **Systeme de plugins** : chaque forme et chaque lumiere est un fichier `.so` charge au demarrage

## Scenes d'exemple

Le dossier `scenes/` contient plusieurs scenes prêtes a rendre :

- `sujet.cfg` : scene principale demandee par le sujet
- `colored_light.cfg` : lumieres de couleurs differentes
- `limited.cfg` : cylindre et cone avec une hauteur
- `reflection.cfg` : objets avec des reflets
- `transparency.cfg` : objets transparents
- `demo_cone_phong.cfg` : cones avec reflets brillants
- `triangle.cfg` : scene avec des triangles

## Documentation

La documentation complete du projet est disponible dans le dossier `docs/`.
