%TKEO con cuantificación de los datos de las señales EMG
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
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Cuantificadores
Q_data = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24 23]);
Q_suma = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24+1 23]);
Q_product = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24+24 23+23]);
Q_out = quantizer('Mode','fixed', 'RoundMode','ceil', 'OverflowMode','saturate', 'Format',[24+2 23]);
%Cuantificación de la normalización
EMG_Q = [zeros(1,1); quantize(Q_data,EMG_Normalizada_ini)];
EMG_Q_ini=quantize(Q_data,EMG_Normalizada_ini);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementaciön del TKEO

bit=6;
N = 2^bit; % TamaÃ±o de la ventan
%Variables para el bucle for

% Bucle for
fin = length(EMG);
EMG_TKEO= zeros(length(EMG),1);


%Bucle for con el algoritmo TKEO
for k=1:1:fin-2
    dataIn = EMG_Q(k+1);
    EMG_sqrt = quantize(Q_data, quantize(Q_product, dataIn^2));
    dataIn_Before=EMG_Q(k);
    dataIn_After=EMG_Q(k+2);
    EMG_product = quantize(Q_data, quantize(Q_product, dataIn_Before*dataIn_After));
    EMG_TKEO(k)= quantize(Q_out, (4*(quantize(Q_data, quantize(Q_suma, EMG_sqrt - EMG_product) ) )));
end



% %Error absoluto medio
MAE= sum(abs(EMG_Normalizada_ini - EMG_Q_ini))/length(EMG_Normalizada_ini);

% %Error cuadrático medio
RMSE = sqrt(sum((EMG_Normalizada_ini - EMG_Q_ini).^2)/length(EMG_Normalizada_ini));

% %1) Datos normalizados de la señal EMG
% %Guardado de datos de la señal EMG normalizados
% data_q = EMG_Q_ini;
% 
% fidir= fopen ('Datain_TKEO_Q.dat', 'w+');
% for cont_q=1:fin
%     sampleh= num2hex(Q_data, (real(data_q(cont_q))));
%     samplei= hex2dec (sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);
% 
% 
% fidhr= fopen ('Datain_TKEO_Q.txt', 'w+');
% for cont_q=1:fin
%     
%     sampleh= real(data_q(cont_q));
%     samplei= sampleh;
%     fprintf (fidhr, '%.9f, ', sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidhr);
% %2) Datos de salida, EMG filtrada con la Media movil(normalizados)
% %Guardado de datos de la señal EMG cuantificada
% dataout = [zeros(1,1); EMG_TKEO];
% 
% fidir= fopen ('Dataout_TKEO_Q.dat', 'w+');
% fidhr= fopen ('Dataout_TKEO_Q.txt', 'w+');
% for cont_f=1:fin
%     sampleh= num2hex(Q_out, (real(dataout(cont_f))));
%     samplei= hex2dec (sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);
% fclose (fidhr);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Representacion grafica de la seÃ±al EMG sacada de la base de datos
close all;
figure (1);
hold on; % Comando para representar varias figuras en una misma ventana
title('Señal EMG');%Titulo de la grÃ¡fica
xlabel('tiempo'); % titulo del eje x

plot (Tiempo,EMG);%Graficar la seÃ±al EMG original
ylabel('EMG');
legend('EMG original');

plot (Tiempo,EMG_Normalizada_ini,'g');
legend('EMG original','EMG normalizada');

plot (Tiempo,EMG_TKEO,'r');
legend('EMG original','EMG normalizada','EMG filtrada(TKEO)');
hold off;
