%TFM RMS movil con bucles for y cuantificacion
%Joaquín Ramos García

clear;
clc;
%Se pueden cambiar los valores de las variables en estas lineas de cÃ³digo tambien
Participante = 8; % Del 1 al 16
MUSCLE = "L_TA"; % L_BF,R_BF,L_TA,R_TA,L_GAL,R_GAL,L_VL,R_VL
VELOC = "V3"; % V1,V15,V2,V25,V3,V35,V4
TRIAL= 1; % Del 1 al 7

Sujeto = "Subject1_raw";
Sujeto = replace(Sujeto, "1", num2str(Participante));

% Cargamos la base de datos
load(["Participant" + Participante + "/" + 'Raw_Data.mat']);


% Seleccionamos los valores de la base de datos de acuerdo a los parÃ¡metros definidos
eval("Senal_Musculo = [" + Sujeto + ".(VELOC).EMG{TRIAL, 2}.Time, " + Sujeto + ".(VELOC).EMG{TRIAL, 2}.(MUSCLE)];");
% Senal_Musculo = [Subject1_raw.(VELOC).EMG{TRIAL, 2}.Time, Subject1_raw.(VELOC).EMG{TRIAL, 2}.(MUSCLE)];
EMG = Senal_Musculo(:, 2);
Tiempo = Senal_Musculo(:, 1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Normalizado del dato
Valor_Max = max(EMG);

EMG_Normalizada=EMG/Valor_Max;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Cuantificadores
Q_data = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24 23]);
Q_suma = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24+6 23]);
Q_product = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24+24 23+23]);

%Cuantificación de la normalización
EMG_Q = [zeros(64,1); quantize(Q_data,EMG_Normalizada)];
EMG_Q_ini  = quantize(Q_data,EMG_Normalizada);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementación de la media móvil
bit=6;
N = 2^bit; % Tamaño de la ventana

%Variables para el bucle for

fin = length(EMG_Q);
EMG_RMS= zeros(length(EMG_Q),1);

% Bucle for
for k=1:1:fin-N
    acumulado=0;
    for j=0+k:1:N+k
        dataIn = EMG_Q(j);
        EMG_sqrt = quantize(Q_data, quantize(Q_product, dataIn^2));
        acumulado = quantize(Q_suma, acumulado + EMG_sqrt);
    end
    EMG_RMS(k)= quantize(Q_data, sqrt(acumulado/N));
end
EMG_RMS_fin = EMG_RMS(1:fin-N);
%2) EMG normalizada 

data_q = EMG_Q_ini;

fidir= fopen ('Datain_RMS_Q.dat', 'w+');

for cont_q=1:fin-N
    sampleh= num2hex(Q_data, (real(data_q(cont_q))));
    samplei= hex2dec (sampleh);
    fwrite (fidir, samplei, 'int32');
end
fclose (fidir);


%3) Datos de salida, EMG filtrada con la Media movil(normalizados)

dataout = EMG_RMS_fin;

fidir= fopen ('Dataout_RMS_Q.dat', 'w+');

for cont_f=1:fin-N
    sampleh= num2hex(Q_data, (real(dataout(cont_f))));
    samplei= hex2dec (sampleh);
    fwrite (fidir, samplei, 'int32');
end
fclose (fidir);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Representación gráfica de la señal EMG sacada de la base de datos
close all;
figure (1);
hold on; % Comando para representar varias figuras en una misma ventana
title('Señal EMG');%Titulo de la grÃ¡fica
xlabel('tiempo'); % titulo del eje x

plot (Tiempo,EMG);%Graficar la seÃ±al EMG original
ylabel('EMG');
legend('EMG original');

plot (Tiempo,EMG_Normalizada,'g');
legend('EMG original','EMG normalizada');

plot (Tiempo,EMG_RMS_fin,'r');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;


