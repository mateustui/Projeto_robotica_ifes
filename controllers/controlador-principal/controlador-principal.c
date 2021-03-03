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
void seguir_linha(WbDeviceTag motorE, WbDeviceTag motorD, int sinal);
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
    
    int opc=0;
    int erro=0;
    float kp=0.005;
    float ki=0.0;
    int erro_soma=0.0;
    int pi=0.0;
    int vel=0;
    while (wb_robot_step(DT) != -1)
    {
    int key = wb_keyboard_get_key();
    double valor = wb_distance_sensor_get_value(d1);

        double s1 = wb_distance_sensor_get_value(l1);
        double s2 = wb_distance_sensor_get_value(l2);
        double s3 = wb_distance_sensor_get_value(l3);
        double s4 = wb_distance_sensor_get_value(l4);
        double s5 = wb_distance_sensor_get_value(l5);
    
      switch(opc)
      {
        case 0://parado
        {
          printf("Parar\n");
          parar(motorE, motorD);
          if (key == 'I')
          {
            opc=1;
          }
          break;
        }
        case 1:
        {
        if (key == 'P')
          {
            opc=0;
          }
          erro=s2-s4;
          pi=erro*kp+erro_soma*ki;
          erro_soma=erro;
          if(erro_soma>10000)
          {
            erro_soma=10000;
          }
          else if(erro_soma<-10000)
          {
            erro_soma=-10000;
          }
          vel=1*pi;
          if(vel>VEL_MAX-2)
          {
            vel=VEL_MAX;
          }
          else if(vel<-(VEL_MAX+2))
          {
            vel=-VEL_MAX;
          }
          seguir_linha( motorE,  motorD, vel);
        break;
        }
        
      
      }
    
        

        printf("| DISTANCIA: %.2f | \t | S1: %.0f | S2: %.0f | S3: %.0f | S4: %.0f | S5: %.0f |\n", valor, s1, s2, s3, s4, s5);

      
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

void seguir_linha(WbDeviceTag motorE, WbDeviceTag motorD, int sinal)
{
    wb_motor_set_velocity(motorE, sinal+2.0 );
    wb_motor_set_velocity(motorD, -sinal+2.0);
}