%Algoritmo TKEO para la detección de envolvente de sales EMG
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
EMG_Normalizada = [zeros(1,1); EMG_Normalizada_ini];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementaciön del TKEO

% Bucle for
fin = length(EMG);
EMG_TKEO= zeros(length(EMG),1);

%Bucle for con el algoritmo TKEO
for k=1:1:fin-2
    EMG_TKEO(k+1)= 4*(EMG_Normalizada(k+1).^2-(EMG_Normalizada(k)*EMG_Normalizada(k+2)));
end


%1) Datos normalizados de la señal EMG
%Guardado de datos de la señal EMG normalizados
data_q = EMG_Normalizada_ini;

fidir= fopen ('Datain_TKEO.dat', 'w+');
fidhr= fopen ('Datain_TKEO.txt', 'w+');
for cont_q=1:fin
    sampleh=  real(data_q(cont_q));
    samplei= sampleh;
    fprintf (fidhr, '%.9f, ', sampleh);
    fwrite (fidir, samplei, 'int32');
end
fclose (fidir);
fclose (fidhr);

%2) Datos de salida, EMG filtrada con la Media movil(normalizados)
%Guardado de datos de la señal EMG cuantificada
dataout = EMG_TKEO;

fidir= fopen ('Dataout_TKEO.dat', 'w+');
fidhr= fopen ('Dataout_TKEO.txt', 'w+');
for cont_f=1:1:fin
    sampleh=  real(dataout(cont_f));
    
    samplei= sampleh;
    fprintf (fidhr, '%.9f, ', sampleh);
    fwrite (fidir, samplei, 'bit24');
end
fclose (fidir);
fclose (fidhr);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Representacion grafica de la seÃ±al EMG sacada de la base de datos
close all;
figure (1);
hold on; % Comando para representar varias figuras en una misma ventana
title('TKEO');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG_Normalizada_ini,'g');%Graficar la señal EMG original
plot (Tiempo,EMG_TKEO,'r');
legend('EMG normalizada','EMG filtrada');
hold off;


%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Abre el archivo .dat para lectura
fid = fopen('Dataout_TKEO_Q.dat', 'r');

% Lee los datos del archivo
%data = fread(fid, Inf, 'bit24');
data = fread(fid, Inf, 'int32');
% Cierra el archivo
fclose(fid);

% Muestra o realiza operaciones con los datos
disp(data);

% Por ejemplo, puedes trazar los datos
figure;
plot(data);
title('Datos desde el archivo .dat');
xlabel('Índice');
ylabel('Valor');
