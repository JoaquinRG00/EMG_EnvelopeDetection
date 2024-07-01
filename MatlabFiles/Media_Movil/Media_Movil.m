%TFM Media movil con bucles for
%Joaquín Ramos García

clear;
clc;
%Se pueden cambiar los valores de las variables en estas lineas de codigo tambien
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
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Rectificación
EMG_rectificada_ini = abs(EMG_Normalizada);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementación de la media movil
bit=6;
N = 2^bit; % Tamaño de la ventana

%Variables para el bucle for
EMG_rectificada = [zeros(N,1); EMG_rectificada_ini];
fin = length(EMG_rectificada);
EMG_filtrada= zeros(length(EMG_rectificada),1);

% Bucle for
for k=1:1:fin-N
    acumulado=0;
    for j=0+k:1:N+k
        acumulado = acumulado + EMG_rectificada(j);
    end
    EMG_filtrada(k)= acumulado/N;
end

EMG_filtrada_fin = EMG_filtrada(1:fin-N);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1) Datos de entrada
%Guardado de datos de entrada de la señal EMG
% datain = EMG;
% 
% fidir= fopen ('Datain_real_EMG_1.dat', 'w+');
% fidhr= fopen ('Datain_real_EMG_1.txt', 'w+');
% for cont=1:9088
%     sampleh=  real(datain(cont));
%     samplei= sampleh;
%     fprintf (fidhr, '%s, ', sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);
% fclose (fidhr);

%2) EMG normalizada 

datain = EMG_Normalizada;

fidir= fopen ('Datain_MM.dat', 'w+');
fidhr= fopen ('Datain_MM.txt', 'w+');
for cont=1:fin-N
    sampleh=  real(datain(cont));
    
    samplei= sampleh;
    fprintf (fidhr, '%.9f, ', sampleh);
    fwrite (fidir, samplei, 'int32');
end
fclose (fidir);
fclose (fidhr);

%3) Datos de salida, EMG filtrada con la Media movil(normalizados)

dataout = EMG_filtrada_fin;

fidir= fopen ('Dataout_MM.dat', 'w+');
fidhr= fopen ('Dataout_MM.txt', 'w+');
for cont_f=1:fin-N
    sampleh=  real(dataout(cont_f));
    
    samplei= sampleh;
    fprintf (fidhr, '%.9f, ', sampleh);
    fwrite (fidir, samplei, 'int32');
end
fclose (fidir);
fclose (fidhr);
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

plot (Tiempo,EMG_rectificada_ini,'g');
legend('EMG original','EMG rectificada');

plot (Tiempo,EMG_filtrada_fin,'r');
legend('EMG original','EMG rectificada','EMG filtrada(Media Movil)');
hold off;
