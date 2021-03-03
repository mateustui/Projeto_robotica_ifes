#include <stdio.h>
#include <webots/keyboard.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#define DT 50
#define VEL_MAX 6.28

void frente(WbDeviceTag motorE, WbDeviceTag motorD);
void tras(WbDeviceTag motorE, WbDeviceTag motorD);
void parar(WbDeviceTag motorE, WbDeviceTag motorD);
void esquerda(WbDeviceTag motorE, WbDeviceTag motorD);
void direita(WbDeviceTag motorE, WbDeviceTag motorD);

int main()
{
    //Inicialização dos parâmetros da simulação
    wb_robot_init();
    
    WbDeviceTag motorE = wb_robot_get_device("motorE");
    WbDeviceTag motorD = wb_robot_get_device("motorD");

    WbDeviceTag d1 = wb_robot_get_device("d1");
    WbDeviceTag l1 = wb_robot_get_device("l1");
    WbDeviceTag l2 = wb_robot_get_device("l2");
    WbDeviceTag l3 = wb_robot_get_device("l3");
    WbDeviceTag l4 = wb_robot_get_device("l4");
    WbDeviceTag l5 = wb_robot_get_device("l5");

    wb_distance_sensor_enable(d1, DT);
    wb_distance_sensor_enable(l1, DT);
    wb_distance_sensor_enable(l2, DT);
    wb_distance_sensor_enable(l3, DT);
    wb_distance_sensor_enable(l4, DT);
    wb_distance_sensor_enable(l5, DT);


    wb_motor_set_position(motorE, INFINITY);
    wb_motor_set_position(motorD, INFINITY);

    wb_motor_set_velocity(motorE, 0.0 * VEL_MAX);
    wb_motor_set_velocity(motorD, 0.0 * VEL_MAX);

    wb_keyboard_enable(DT);

    while (wb_robot_step(DT) != -1)
    {
        double valor = wb_distance_sensor_get_value(d1);

        double s1 = wb_distance_sensor_get_value(l1);
        double s2 = wb_distance_sensor_get_value(l2);
        double s3 = wb_distance_sensor_get_value(l3);
        double s4 = wb_distance_sensor_get_value(l4);
        double s5 = wb_distance_sensor_get_value(l5);

        int key = wb_keyboard_get_key();

        printf("| DISTANCIA: %.2f | \t | S1: %.0f \t S2: %.0f \t S3: %.0f \t S4: %.0f \t S5: %.0f |\n", valor, s1, s2, s3, s4, s5);

        if (key == 'I')
        {
            printf("Frente\n");
            frente(motorE, motorD);
        }
        else if (key == 'K')
        {
            printf("Tras\n");
            tras(motorE, motorD);
        }
        else if (key == 'J')
        {
            printf("Esquerda\n");
            esquerda(motorE, motorD);
        }
        else if (key == 'L')
        {
            printf("Direita\n");
            direita(motorE, motorD);
        }
        else if (key == 'P')
        {
            printf("Parar\n");
            parar(motorE, motorD);
        }
    }

    wb_robot_cleanup();

    return 0;
}

void frente(WbDeviceTag motorE, WbDeviceTag motorD)
{
    wb_motor_set_velocity(motorE, 0.2 * VEL_MAX);
    wb_motor_set_velocity(motorD, 0.2 * VEL_MAX);
}

void tras(WbDeviceTag motorE, WbDeviceTag motorD)
{
    wb_motor_set_velocity(motorE, -0.2 * VEL_MAX);
    wb_motor_set_velocity(motorD, -0.2 * VEL_MAX);
}

void esquerda(WbDeviceTag motorE, WbDeviceTag motorD)
{
    wb_motor_set_velocity(motorE, -0.2 * VEL_MAX);
    wb_motor_set_velocity(motorD, 0.2 * VEL_MAX);
}

void direita(WbDeviceTag motorE, WbDeviceTag motorD)
{
    wb_motor_set_velocity(motorE, 0.5 * VEL_MAX);
    wb_motor_set_velocity(motorD, -0.5 * VEL_MAX);
}

void parar(WbDeviceTag motorE, WbDeviceTag motorD)
{
    wb_motor_set_velocity(motorE, 0.0 * VEL_MAX);
    wb_motor_set_velocity(motorD, 0.0 * VEL_MAX);
}