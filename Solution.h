
#ifndef SOLUTION_H
#define SOLUTION_H

#endif // SOLUTION_H


double T_medium(double T1, double T2);

double Term_pressure(int type, double T1_h, double T2_h, double T1_c, double T2_c);

double Power(double T1, double T2, double d_mass, double heat_capacity);

double Tubes_area_d(double d);

double Tubes_area_D(double d, double D, double delt);

double Flow_rate(double Area_tube, double d_mass, double density);

double Reynolds(double velocity, double d, double koef_kin);

double Nusselt_d(double Reynolds, double Prandtl);

double Nusselt_D(double Reynolds, double Prandtl, double d, double D);

double Heat_transfer_coef(double Nuselt, double Thermal_conduc, double d);

double Heat_transfer(double Heat_transfer_coef_hot, double Heat_transfer_coef_cold, double delt, double thermal_conduc_metall);

double Square(double power, double k, double delt_T);

double Lenght(double F, int n, double d);

double Area_tube(double d);

double M(double d, double d_mass, double density, int type_lattice, double v);

int Tubes_number(double m, int type_lattice);

double Area_tubes(double d, double n);

double Outer_diameter(double m, double h, double delt_d);

double Area_interpipe(double d, double m, double h, double delt_d, double n);

double Equivalent_diameter(double d, double m, double h, double delt_d, double n);

double Flow_rate(double d, double n, double d_mass, double density);

double Flow_rate_intertube(double area_interpipe, double d_mass, double density);

double Nusselt(double Reynolds, double Prandtl, int type);

double Dimension_T(int type, double num);

double Dimension_P(int type, double num);

double Dimension_dmass(int type, double num);

double Dimension_d(int type, double num);

double Dimension_d(int type, double num);

double Dimension_v(int type, double num);
