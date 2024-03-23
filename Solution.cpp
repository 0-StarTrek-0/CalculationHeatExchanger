#include <QtMath>
#include "Solution.h"

double T_medium(double T1, double T2)
{
    return (T1 + T2)/2.0;
}

double Term_pressure(int type, double T1_h, double T2_h, double T1_c, double T2_c)
{
    double eps = 0.85;		//Поправочный коэф. для противотока
    /*
    current_type = 1 - для противотока;
    current_type = 2 - для прямотока.
    */
    if (type == 0)
        return eps * ((T1_h - T1_c) - (T2_h - T2_c)) / (qLn((T1_h - T1_c) - (T2_h - T2_c)));
    else if (type == 1)
        return ((T1_h - T2_c) + (T2_h - T1_c)) / 2;
    else
        return -1.0;
}

double Power(double T1, double T2, double d_mass, double heat_capacity)
{
    if (T1 > T2)
        return heat_capacity * d_mass * (T1 - T2);
    else
        return heat_capacity * d_mass * (T2 - T1);
}

double Tubes_area_d(double d)
{
    return d*d*M_PI/4;
}

double Tubes_area_D(double d, double D, double delt)
{
    return M_PI*(D*D - (d - delt)*(d - delt))/4;
}

double Flow_rate(double Area_tube, double d_mass, double density)
{
    return d_mass / (Area_tube * density);
}

double Reynolds(double velocity, double d, double koef_kin)
{
    return velocity * d / koef_kin;
}

double Nusselt_d(double Reynolds, double Prandtl)
{
    if (Reynolds > 10000)
        return 0.021 * qPow(Reynolds, 0.8) * qPow(Prandtl, 0.43);
    else
        return 0.28 * qPow(Reynolds, 0.6) * qPow(Prandtl, 0.36) * 1;
}

double Nusselt_D(double Reynolds, double Prandtl, double d, double D)
{
    if (Reynolds > 10000)
        return 0.017 * qPow(Reynolds, 0.8) * qPow(Prandtl, 0.4) * qPow(D/d, 0.18);
    else
        return 0.21 * qPow(Reynolds, 0.6) * qPow(Prandtl, 0.36) * 1;
}

double Heat_transfer_coef(double Nuselt, double Thermal_conduc, double d)
{
    return Nuselt * Thermal_conduc / d;
}

double Heat_transfer(double Heat_transfer_coef_hot, double Heat_transfer_coef_cold, double delt, double thermal_conduc_metall)
{
    return 1 / (1/Heat_transfer_coef_hot + delt/thermal_conduc_metall + 1/Heat_transfer_coef_cold);
}

double Square(double power, double k, double delt_T)
{
    return power/(k * delt_T);
}

double Lenght(double F, int n, double d)
{
    return F / (n * M_PI * d);
}

double Area_tube(double d)
{
    return M_PI * d * d / 4;
}

double M(double d, double d_mass, double density, int type_lattice, double v)
{
    double b = 3, a = 3, c;
    double Discr;
    switch (type_lattice) {
    case 0:
        c = 1 - 4 * d_mass / (v * density * M_PI * d * d);
        Discr = b * b - 4 * a * c;
        if (Discr > 0) {
            return ceil((-b + sqrt(Discr)) / (2 * a));
        }
        else if (Discr == 0) {
            return ceil(-b / (2 * a));
        }
        else {
            return 1;
        }
        break;
    case 1:
        c = 1 - 2 * d_mass / (v * density * M_PI * M_PI * d * d);
        Discr = b * b - 4 * a * c;
        if (Discr > 0)
            return ceil((-b + sqrt(Discr)) / (2 * a));
        else if (Discr == 0)
            return ceil(-b / (2 * a));
        else
            return 1;
        break;
    case 2:
        c = 4 * d_mass / (v * density * M_PI * d * d);
        if (c > 0)
            return sqrt(c);
        else
            return 1;
        break;
    }
}

int Tubes_number(double m, int type_lattice)
{
    int sum = 1;
    switch (type_lattice) {
    case 0:
        return 1 + 3 * m + 3 * m*m;
        break;
    case 1:
        for (int i=0; i < m; i++)
            sum += i*6;
        return sum;
        break;
    case 2:
        if (m >1)
            return m * m;
        else
            return 1;
        break;
    }
}

double Area_tubes(double d, double n)
{
    return n * Area_tube(d);
}

double Outer_diameter(double m, double h, double delt_d)
{
    return (2 * m + 1) * h + 2 * delt_d;
}

double Area_interpipe(double d, double m, double h, double delt_d, double n)
{
    return M_PI * (Outer_diameter(m, h, delt_d) * Outer_diameter(m, h, delt_d) - n * d * d)/4;
}

double Equivalent_diameter(double d, double m, double h, double delt_d, double n)
{
    double U;
    U = M_PI * (Outer_diameter(m, h, delt_d) + n * d);
    return 4 * Area_interpipe(d, m, h, delt_d, n) / U;
}

double Flow_rate(double d, double n, double d_mass, double density)
{
    return d_mass / (Area_tubes(d, n) * density);
}

double Flow_rate_intertube(double area_interpipe, double d_mass, double density)
{
    return d_mass / (area_interpipe * density);
}

double Nusselt(double Reynolds, double Prandtl, int type)
{
    switch (type) {
    case 0:
        if (Reynolds > 10000)
            return 0.023 * qPow(Reynolds, 0.8) * qPow(Prandtl, 0.4) * 1;
        else
            return 0.21 * qPow(Reynolds, 0.6) * qPow(Prandtl, 0.36) * 1;
        break;
    case 1:
        if (Reynolds > 10000)
            return 0.023 * qPow(Reynolds, 0.8) * qPow(Prandtl, 0.4) * 1;
        else
            return 0.21 * qPow(Reynolds, 0.6) * qPow(Prandtl, 0.36) * 1;
        break;
    default:
        break;
    }
}

double Dimension_T(int type, double num)
{
    switch (type) {
    case 0:     //оС
        return num;
        break;
    case 1:     //К
        return num - 273.15;
        break;
    }
}

double Dimension_P(int type, double num)
{
    switch (type) {
    case 0:     //кПа
        return num;
        break;
    case 1:     //МПА
        return num * 1000;
        break;
    case 2:     //Па
        return num / 1000;
        break;
    case 3:     //кгс/см2
        return num * 98.0665;
        break;
    case 4:     //атм
        return num * 98.0665;
        break;
    case 5:     //бар
        return num * 100;
        break;
    case 6:     //мм рт. ст.
        return num / 7.501;
        break;
    case 7:     //мм вод. ст.
        return num / 101.9744;
        break;
    }
}

double Dimension_dmass(int type, double num)
{
    switch (type) {
    case 0:     //кг/с
        return num;
        break;
    case 1:     //кг/мин
        return num / 60;
        break;
    case 2:     //кг/ч
        return num / 3600;
        break;
    case 3:     //г/с
        return num / 1000;
        break;
    case 4:     //г/мин
        return num / 1000 / 60;
        break;
    case 5:     //г/ч
        return num / 1000 / 3600;
        break;
    }
}

double Dimension_d(int type, double num)
{
    switch (type) {
    case 0:
        return num / 1000;
        break;
    case 1:
        return num / 100;
        break;
    case 2:
        return num;
        break;
    }
}

double Dimension_v(int type, double num)
{
    switch (type) {
    case 0:
        return num;
        break;
    case 1:
        return num * 10;
        break;
    case 2:
        return num * 1000;
        break;
    case 3:
        return num / 60;
        break;
    case 4:
        return num / 3600;
        break;
    }
}
