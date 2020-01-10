
/****** Simple Neural Network Implementation to predict sin(x) function
 *      train using tensorflow
 * 
 *      Roberto del Campo
 * 
 * /

/*Model: "sequential_1"
_________________________________________________________________
Layer (type)                 Output Shape              Param #   
=================================================================
dense_3 (Dense)              multiple                  20        
_________________________________________________________________
dense_4 (Dense)              multiple                  33        
_________________________________________________________________
dense_5 (Dense)              multiple                  4         
=================================================================
Total params: 57
Trainable params: 57
Non-trainable params: 0
*/

#include <Arduino.h>
#include <math.h>

double a0[10] = {0.23734964,  0.48597103,  0.08157657,  0.32443246, -0.65180147,
         -0.41175422, -0.5986737 , -0.9380558 ,  0.93573976, -0.35141608};
double b0[10] = {-0.04088326,  0.1823307 , -0.44747925,  0.12661895,  1.6965402 ,
         1.581996  , -0.03595349,  0.17232893, -0.20738754,  2.0182164 };

double a1[30]= { -0.40439576, -0.15013483,  0.73700345,
         0.3600316 ,  0.4522304 , -0.45662746,
        -0.25484255, -0.6329525 ,  0.4304328 ,
         0.1008125 , -0.3812547 ,  0.5619081 ,
        -0.9959041 , -1.0859134 , -0.97423446,
        -0.69124174, -0.04537146, -1.3087047 ,
         0.1492916 , -0.19478774, -0.06880233,
        -0.0449551 ,  0.80907434,  0.5545898 ,
        -0.5362559 , -0.6172974 , -0.06039093,
        -0.50300616,  1.3802997 , -1.3889508};

double b1[3] ={0.32874614, 0.29079342, 0.3546584};
double a2[3]={-0.57490975,-2.6296918,-1.0484772};
double b2=0.36710465;
double y[33];

double softsign (double x)
{
    double y;
    y = x /( 1+ abs(x));
    return y;
}


void neuron (int n_inputs, int n_nodes, double weights[], double bias[], double inputs[])
{
    int i;
    int j;

    Serial.println("Inicio Calculo....");
    for (i=0; i<n_nodes;i++)
    {
        y[i]=0;    
        for (j=0;j<n_inputs;j++)
            y[i]= y[i]+weights[n_nodes*j+i]*inputs[j];

        y[i]=y[i]+bias[i];
        
        //Activation function
        y[i]= softsign(y[i]);
    }

}

void setup() 
{
    Serial.begin(115200);
    Serial.println("Waiting input Data....");
    
  
}


void loop() 
{
    double input;
    double z[33];
    double res=0;
    int i;
    

    while (Serial.available()==0)  {
    }
       
    //Input Layer

    input = Serial.parseFloat();
    Serial.flush();
    
    if(input < 0.0f || input > (float)(2*PI)) 
    {
		Serial.println("Your number must be greater than 0 and less than 2*PI");
		return;
	}
        
    Serial.println("Running inference on inputted data...");	
    
    //Input Layer
    double in[]={input}; 

    //1st Hidden Layer
    neuron(1, 10, a0, b0, in);
    
    
    for (i=0; i <10; i++)
        z[i] = y[i];
        
    //Second Hidden Layer
    neuron (10, 3, a1, b1, z);


    //Output Layer
    for (i=0;i<3;i++)
        res= res+ a2[i]*y[i];
    
    res=res+b2;

    //Predictions and error
    Serial.println("Prediction");
    Serial.println(res,4);
    Serial.println("Target");
    Serial.println(sin(input),4);
    Serial.println("Error");
    Serial.println(abs(res-sin(input)),4);
    
}