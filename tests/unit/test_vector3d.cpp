/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** tests Vector3D
*/

#include <criterion/criterion.h>
#include "types.hpp"

using RayTracer::Vector3D;

Test(Vector3D, constructeur_par_defaut)
{
    Vector3D v;
    cr_assert_float_eq(v.x, 0, 1e-6);
    cr_assert_float_eq(v.y, 0, 1e-6);
    cr_assert_float_eq(v.z, 0, 1e-6);
}

Test(Vector3D, constructeur_avec_valeurs)
{
    Vector3D v(1, 2, 3);
    cr_assert_float_eq(v.x, 1, 1e-6);
    cr_assert_float_eq(v.y, 2, 1e-6);
    cr_assert_float_eq(v.z, 3, 1e-6);
}

Test(Vector3D, addition)
{
    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    Vector3D resultat = a + b;
    cr_assert_float_eq(resultat.x, 5, 1e-6);
    cr_assert_float_eq(resultat.y, 7, 1e-6);
    cr_assert_float_eq(resultat.z, 9, 1e-6);
}

Test(Vector3D, soustraction)
{
    Vector3D a(4, 5, 6);
    Vector3D b(1, 2, 3);
    Vector3D resultat = a - b;
    cr_assert_float_eq(resultat.x, 3, 1e-6);
    cr_assert_float_eq(resultat.y, 3, 1e-6);
    cr_assert_float_eq(resultat.z, 3, 1e-6);
}

Test(Vector3D, multiplication_scalaire)
{
    Vector3D v(1, 2, 3);
    Vector3D resultat = v * 2;
    cr_assert_float_eq(resultat.x, 2, 1e-6);
    cr_assert_float_eq(resultat.y, 4, 1e-6);
    cr_assert_float_eq(resultat.z, 6, 1e-6);
}

Test(Vector3D, division_scalaire)
{
    Vector3D v(4, 6, 8);
    Vector3D resultat = v / 2;
    cr_assert_float_eq(resultat.x, 2, 1e-6);
    cr_assert_float_eq(resultat.y, 3, 1e-6);
    cr_assert_float_eq(resultat.z, 4, 1e-6);
}

Test(Vector3D, produit_scalaire)
{
    Vector3D a(1, 2, 3);
    Vector3D b(4, 5, 6);
    cr_assert_float_eq(a.dot(b), 32, 1e-6);
}

Test(Vector3D, produit_vectoriel)
{
    Vector3D a(1, 0, 0);
    Vector3D b(0, 1, 0);
    Vector3D resultat = a.cross(b);
    cr_assert_float_eq(resultat.x, 0, 1e-6);
    cr_assert_float_eq(resultat.y, 0, 1e-6);
    cr_assert_float_eq(resultat.z, 1, 1e-6);
}

Test(Vector3D, longueur)
{
    Vector3D v(3, 4, 0);
    cr_assert_float_eq(v.length(), 5, 1e-6);
}

Test(Vector3D, normalisation)
{
    Vector3D v(3, 0, 0);
    Vector3D resultat = v.normalize();
    cr_assert_float_eq(resultat.x, 1, 1e-6);
    cr_assert_float_eq(resultat.y, 0, 1e-6);
    cr_assert_float_eq(resultat.z, 0, 1e-6);
}

Test(Vector3D, normalisation_vecteur_nul)
{
    Vector3D v(0, 0, 0);
    Vector3D resultat = v.normalize();
    cr_assert_float_eq(resultat.x, 0, 1e-6);
    cr_assert_float_eq(resultat.y, 0, 1e-6);
    cr_assert_float_eq(resultat.z, 0, 1e-6);
}
