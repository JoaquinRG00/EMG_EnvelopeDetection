%TFM
%Joaquín Ramos García

clear;
clc;
%Se pueden cambiar los valores de las variables en estas lineas de código tambien
Participante = 8; % Del 1 al 16
MUSCLE = "L_TA"; % L_BF,R_BF,L_TA,R_TA,L_GAL,R_GAL,L_VL,R_VL
VELOC = "V3"; % V1,V15,V2,V25,V3,V35,V4
TRIAL= 1; % Del 1 al 7

% %Solicitud de participante
% % disp("Elija el participante que quiere estudiar");
% Participante = input("Ingrese un número del participante: ");
Sujeto = "Subject1_raw";
Sujeto = replace(Sujeto, "1", num2str(Participante));


% %Solicitud del músculo que se quiere estudiar
% disp("Elija el músculo que quiere estudiar, Las opciones son : L_BF,R_BF,L_TA,R_TA,L_GAS,R_GAS,L_SOL,R_SOL");
% MUSCLE = input('Por favor, ingrese el musculo: ','s');
% 
% %Solicitud de la velocidad que se quiere estudiar
% disp("Elija la velocidad que quiere estudiar, Las opciones son : V1,V15,V2,V25,V3,V35,V4");
% VELOC = input('Por favor, ingrese la velocidad: ','s');
% 
% %Solicitud del trial que se quiere estudiar
% disp("Elija el trial que quiere estudiar, Las opciones son : 1,2,3,4,5,6,7");
% TRIAL = input("Por favor, ingrese el trial: ");

% Cargamos la base de datos
load(["Participant" + Participante + "/" + 'Raw_Data.mat']);


% Seleccionamos los valores de la base de datos de acuerdo a los parámetros definidos
eval("Senal_Musculo = [" + Sujeto + ".(VELOC).EMG{TRIAL, 2}.Time, " + Sujeto + ".(VELOC).EMG{TRIAL, 2}.(MUSCLE)];");
% Senal_Musculo = [Subject1_raw.(VELOC).EMG{TRIAL, 2}.Time, Subject1_raw.(VELOC).EMG{TRIAL, 2}.(MUSCLE)];
EMG = Senal_Musculo(:, 2);
Tiempo = Senal_Musculo(:, 1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Rectificación
EMG_rectificada = abs(EMG);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementación del filtro FIR variando el orden
fc1 = 150; % Frecuencia de corte en Hz
fc2 = 100; % Frecuencia de corte en Hz

fc3 = 10; % Frecuencia de corte en Hz
fm= 2000;% Frecuencia de muestreo en Hz
bit=6;
N1 = 8; % Orden del filtro1
N2 = 128; % Orden del filtro2

N3 = 128; % Orden del filtro3

wn1=fc1/(fm/2);% Frecuencia de corte normalizada
wn2=fc2/(fm/2);% Frecuencia de corte normalizada
wn3=fc3/(fm/2);% Frecuencia de corte normalizada
% Diseñar filtro paso bajo
b1= fir1(N1, wn1, "low");
b2= fir1(N2, wn2, "low");
b3= fir1(N3, wn3, "low");
% Aplicación del filtro
EMG_filtrada1 = filter(b1, 1, EMG_rectificada);% El 1 representa que no hay realimentación
EMG_filtrada2 = filter(b2, 1, EMG_rectificada);% El 1 representa que no hay realimentación
EMG_filtrada3 = filter(b3, 1, EMG_rectificada);% El 1 representa que no hay realimentación

% %Implementación del filtro
% fc = 100; % Frecuencia de corte en Hz
% orden = 4; % Orden del filtro
% 
% % Diseñar filtro paso bajo
% filtro_pasabajo = designfilt('lowpass', 'CutoffFrequency', fc, 'FilterOrder', orden);
% 
% % Aplicación del filtro
% EMG_filtrada = filter(b, a, EMG_rectificada);
% %Implementación del filtro
% %He usado la aproximación de Butterworth
% fs = 1000;     % Frecuencia de muestreo
% fc = 100;      % Frecuencia de corte
% orden = 4;     % Orden del filtro
% 
% % Diseño del filtro
% [b, a] = butter(orden, fc/(fs/2), 'low');  % Filtro Butterworth
% 
% % Aplicación del filtro
% EMG_filtrada = filter(b, a, EMG_rectificada);


% %Implementación del filtro
% %He usado la aproximación de Chebyshev
% fs = 1000;          % Frecuencia de muestreo
% fc = 200;           % Frecuencia de corte
% Rp = 3;             % Atenuación máxima permitida en la banda de paso (en dB)
% Wp = fc/(fs/2);     % Frecuencia de corte normalizada
% 
% % Diseñar filtro de Chebyshev tipo IIR de paso bajo
% n = 6;                      % Orden del filtro
% [b, a] = cheby1(n, Rp, Wp, 'low'); 
% 
% % Aplicación del filtro
% EMG_filtrada = filter(b, a, EMG_rectificada);



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Representacion grafica de la señal EMG sacada de la base de datos
close all;
%Subplot1
%subplot(2, 2, 1); % 2 filas, 2 columnas, posición 1
% hold on; % Comando para representar varias figuras en una misma ventana
% title('Filtro con fc=150Hz y Orden 128');%Titulo de la gráfica
% xlabel('Tiempo'); % titulo del eje x
% ylabel('EMG');
% plot (Tiempo,EMG);%Graficar la señal EMG original
% plot (Tiempo,EMG_rectificada,'r');
% plot (Tiempo,EMG_filtrada1,'g');
% legend('EMG original','EMG rectificada','EMG filtrada');
% hold off;

%Subplot2
% subplot(2, 2, 2); % 2 filas, 2 columnas, posición 1
% hold on; % Comando para representar varias figuras en una misma ventana
% title('Filtro con fc=100Hz y Orden 128');%Titulo de la gráfica
% xlabel('Tiempo'); % titulo del eje x
% ylabel('EMG');
% plot (Tiempo,EMG);%Graficar la señal EMG original
% plot (Tiempo,EMG_rectificada,'r');
% plot (Tiempo,EMG_filtrada2,'g');
% legend('EMG original','EMG rectificada','EMG filtrada');
% hold off;
% 
% 
% %Subplot3
% subplot(2, 2, 3); % 2 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title(['Filtro con fc=10Hz y Orden 128']);%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG);%Graficar la señal EMG original
plot (Tiempo,EMG_rectificada,'r');
plot (Tiempo,EMG_filtrada3,'g');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;
