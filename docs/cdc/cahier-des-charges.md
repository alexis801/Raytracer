# Cahier des Charges - Raytracer

## 1. Presentation du projet

### 1.1 Qu'est-ce que c'est ?

Le Raytracer est un programme qui fabrique des images en 3D. On lui donne un fichier qui decrit une scene (des objets, des lumieres, une camera) et il produit une image realiste.

Le principe : pour chaque pixel de l'image, le programme trace un rayon imaginaire depuis la camera vers la scene. Quand le rayon touche un objet, le programme calcule la couleur de ce point en tenant compte des lumieres et des ombres.

### 1.2 Qui est l'equipe ?

3 etudiants d'Epitech (Promo 2029), dans le cadre du module G-OOP-400.

### 1.3 Cadre

- **Module** : G-OOP-400 (Programmation Orientee Objet)
- **Langage** : C++
- **Systeme de build** : CMake + Makefile wrapper

---

## 2. Objectifs

### 2.1 Objectif principal

Developper un raytracer fonctionnel qui :
- Lit un fichier de scene au format libconfig
- Calcule le rendu de la scene pixel par pixel
- Produit une image au format PPM

### 2.2 Objectifs secondaires

- Architecture propre et extensible (interfaces, plugins)
- Utilisation pertinente de design patterns
- Code maintenable et testable

---

## 3. Fonctionnalites

### 3.1 Obligatoires (MUST)

Ce sont les fonctionnalites sans lesquelles le projet est considere comme incomplet.

| # | Fonctionnalite | Description simple |
|---|----------------|--------------------|
| M1 | Sphere | Forme 3D ronde, comme une balle |
| M2 | Plan | Surface plate et infinie, comme un sol |
| M3 | Translation | Deplacer un objet dans l'espace (gauche/droite, haut/bas, avant/arriere) |
| M4 | Lumiere directionnelle | Lumiere qui vient d'une direction, comme le soleil |
| M5 | Lumiere ambiante | Lumiere de base qui eclaire tout uniformement |
| M6 | Couleur unie | Chaque objet a une couleur |
| M7 | Configuration de scene | La scene est decrite dans un fichier texte (.cfg) |
| M8 | Camera configurable | Position, orientation et champ de vision de la camera |
| M9 | Sortie PPM | L'image est generee au format PPM (format d'image simple) |

### 3.2 Recommandees (SHOULD)

A faire une fois que les fonctionnalites obligatoires marchent.

| # | Fonctionnalite | Description simple |
|---|----------------|--------------------|
| S1 | Cylindre | Forme 3D en tube, comme un poteau |
| S2 | Cone | Forme 3D pointue, comme un cornet de glace |
| S3 | Rotation | Tourner un objet sur lui-meme |
| S4 | Ombres portees | Un objet bloque la lumiere et projette une ombre sur les autres |

### 3.3 Bonus (COULD)

Fonctionnalites supplementaires, chacune rapporte des points bonus.

#### Formes supplementaires
| Fonctionnalite | Points | Description |
|----------------|--------|-------------|
| Cylindre limite | 0.5 | Cylindre avec une hauteur maximale (pas infini) |
| Cone limite | 0.5 | Cone avec une hauteur maximale |
| Tore | 1 | Forme de donut |
| Tanglecube | 1 | Forme mathematique complexe |
| Triangles | 1 | Forme de base pour les modeles 3D |
| Fichiers .OBJ | 1 | Importer des modeles 3D depuis des fichiers standards |
| Fractales | 2 | Formes auto-similaires (ex: Mandelbrot 3D) |
| Ruban de Mobius | 2 | Surface a une seule face |

#### Transformations supplementaires
| Fonctionnalite | Points | Description |
|----------------|--------|-------------|
| Echelle | 0.5 | Agrandir ou reduire un objet |
| Cisaillement | 0.5 | Deformer un objet en le "penchant" |
| Matrice de transformation | 2 | Toutes les transformations en une seule matrice |
| Graphe de scene | 2 | Organiser les objets en arbre hierarchique |

#### Lumieres et eclairage
| Fonctionnalite | Points | Description |
|----------------|--------|-------------|
| Plusieurs lumieres directionnelles | 0.5 | Plusieurs sources de lumiere parallele |
| Plusieurs lumieres ponctuelles | 0.5 | Plusieurs sources de lumiere en un point |
| Lumiere coloree | 0.5 | Les lumieres ont une couleur |
| Modele de Phong | 2 | Eclairage realiste avec reflets brillants |
| Occlusion ambiante | 2 | Assombrissement dans les coins et creux |

#### Materiaux et textures
| Fonctionnalite | Points | Description |
|----------------|--------|-------------|
| Transparence | 0.5 | On voit a travers l'objet |
| Refraction | 1 | La lumiere se courbe en traversant l'objet (comme un verre d'eau) |
| Reflexion | 0.5 | L'objet reflete ce qui l'entoure (comme un miroir) |
| Texture depuis fichier | 1 | Appliquer une image sur un objet |
| Texture damier | 1 | Motif de cases noires et blanches |
| Texture Perlin | 1 | Motif pseudo-aleatoire (pour simuler bois, marbre, etc.) |
| Normal mapping | 2 | Simuler des details de surface sans ajouter de geometrie |

#### Interface
| Fonctionnalite | Points | Description |
|----------------|--------|-------------|
| Affichage en temps reel | 1 | Voir l'image se construire pixel par pixel |
| Quitter proprement | 0.5 | Pouvoir fermer l'application pendant ou apres le rendu |
| Apercu rapide | 2 | Version basse resolution pour voir le resultat vite |
| Rechargement auto | 1 | L'image se recalcule quand le fichier de scene change |

#### Optimisations
| Fonctionnalite | Points | Description |
|----------------|--------|-------------|
| Partitionnement spatial | 2 | Organiser l'espace pour tester moins d'intersections |
| Multithreading | 1 | Utiliser plusieurs coeurs du processeur en parallele |
| Rendu distribue | 3 | Repartir le calcul sur plusieurs machines en reseau |

---

## 4. Contraintes techniques

### 4.1 Langage et compilation
- Langage : **C++17**
- Build : **CMake** + **Makefile** (regles : `all`, `clean`, `fclean`, `re`)
- Binaire : `raytracer` a la racine du projet
- Plugins : fichiers `.so` dans `./plugins/`

### 4.2 Bibliotheques autorisees
- Standard library C et C++
- `libconfig++` pour parser les fichiers de scene
- `SFML` pour l'affichage graphique (bonus)
- `libdl` pour le chargement dynamique de plugins

Aucune autre bibliotheque n'est autorisee sans accord de l'equipe pedagogique.

### 4.3 Architecture obligatoire
- **Interfaces** (classes abstraites) pour les primitives et les lumieres
- **Au moins 2 design patterns** parmi : Factory, Builder, Composite, Decorator, Observer, State, Mediator
- Les choix de design patterns seront justifies en soutenance

### 4.4 Gestion des erreurs
- Les erreurs s'affichent sur la sortie d'erreur (`stderr`)
- Le programme retourne **84** en cas d'erreur, **0** sinon

### 4.5 Livraison
- Tout le code source doit etre livre (pas de binaires)
- Les bonus sont dans un dossier `bonus/`
- Des scenes de demo et des screenshots doivent etre prepares pour la soutenance

---

## 5. Format d'entree

### 5.1 Ligne de commande

```
./raytracer <SCENE_FILE>
```

- `SCENE_FILE` : chemin vers un fichier de scene `.cfg`
- `--help` : affiche l'aide

### 5.2 Fichier de scene

Format libconfig++ avec 3 sections principales :

1. **camera** : position, orientation, resolution, champ de vision
2. **primitives** : liste des objets avec leurs proprietes (position, taille, couleur)
3. **lights** : configuration des lumieres (ambiante, directionnelle, ponctuelle)

---

## 6. Format de sortie

Image au format **PPM** (Portable Pixmap) sur la sortie standard.

Le format PPM est un format d'image simple en texte :
```
P3
1920 1080
255
r g b r g b r g b ...
```

- `P3` : identifiant du format (PPM en ASCII)
- `1920 1080` : largeur et hauteur en pixels
- `255` : valeur maximale d'une composante de couleur
- Ensuite, 3 nombres (rouge, vert, bleu) par pixel

---

## 7. Planning previsionnel

### Phase 1 : Fondations
- Mise en place du projet (CMake, structure, CI)
- Interfaces (`IPrimitive`, `ILight`)
- Moteur de rendu de base (lancer de rayons)
- Camera et sortie PPM

### Phase 2 : Fonctionnalites obligatoires
- Sphere + Plan
- Lumiere directionnelle + ambiante
- Translation
- Couleur unie
- Parseur de scene (libconfig++)

### Phase 3 : Fonctionnalites recommandees
- Cylindre + Cone
- Rotation
- Ombres portees

### Phase 4 : Bonus et polish
- Plugins
- Features bonus selectionnees
- Scenes de demo pour la soutenance
- Screenshots

---

## 8. Criteres de validation

Le projet est considere comme reussi si :

1. `make` compile le projet sans erreur
2. `./raytracer scene.cfg > image.ppm` produit une image correcte
3. Les spheres, plans, lumieres et translations fonctionnent
4. Les fichiers de scene sont correctement parses
5. Les erreurs sont gerees proprement (exit 84 + message sur stderr)
6. Le code utilise des interfaces et au moins 2 design patterns
7. Le code compile avec les flags de warning stricts
