%TFM RMS movil con bucles for
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

EMG_Normalizada_ini=EMG/Valor_Max;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementacion de la RMS
bit=7;
N = 2^bit; % Tamaño de la ventana

%Variables para el bucle for

EMG_Normalizada = [zeros(N,1); EMG_Normalizada_ini];
fin = length(EMG_Normalizada);
EMG_RMS= zeros(length(EMG_Normalizada),1);

% Bucle for
for k=1:1:fin-N
    acumulado=0;
    for j=0+k:1:N+k
        acumulado = acumulado + EMG_Normalizada(j)^2;
    end
    EMG_RMS(k)=sqrt(acumulado/N);
end

EMG_RMS_fin = EMG_RMS(1:fin-N);
EMG_RMS_fin2=EMG_RMS_fin.^2;
%2) EMG normalizada 

% datain = EMG_Normalizada_ini;
% 
% fidir= fopen ('Datain_RMS2.dat', 'w+');
% fidhr= fopen ('Datain_RMS2.txt', 'w+');
% for cont=1:fin-N
%     sampleh=  real(datain(cont));
%     
%     samplei= sampleh;
%     fprintf (fidhr, '%.9f, ', sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);
% fclose (fidhr);

%3) Datos de salida, EMG filtrada con la Media movil(normalizados)

% dataout = EMG_RMS_fin;
% 
% fidir= fopen ('Dataout_RMS2.dat', 'w+');
% fidhr= fopen ('Dataout_RMS2.txt', 'w+');
% for cont_f=1:fin-N
%     sampleh=  real(dataout(cont_f));
%     
%     samplei= sampleh;
%     fprintf (fidhr, '%.9f, ', sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);
% fclose (fidhr);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Representación gráfica de la señal EMG sacada de la base de datos
close all;
%Subplot1
subplot(1, 2, 1); % 1 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title('RMS Móvil');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG,'g');%Graficar la señal EMG original
plot (Tiempo,EMG_RMS_fin,'r');
legend('EMG original','EMG filtrada');
hold off;

%Subplot2
subplot(1, 2, 2); % 1 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title('RMS Móvil al cuadrado');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG,'g');%Graficar la señal EMG original
plot (Tiempo,EMG_RMS_fin2,'r');
legend('EMG original','EMG filtrada');
hold off;
