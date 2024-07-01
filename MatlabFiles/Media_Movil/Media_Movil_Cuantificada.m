TFM Media movil con bucles for y con cuantificación
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

%Cuantificación de la normalización
EMG_Q = quantize(Q_data,EMG_Normalizada);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Rectificación
EMG_rectificada_Q_ini = abs(EMG_Q);
%EMG_rectificada = abs(EMG);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Implementación de la media movil
bit=6;
N = 2^bit; % Tamaño de la ventana

EMG_rectificada_Q = [zeros(N,1); EMG_rectificada_Q_ini];
fin = length(EMG_rectificada_Q);
EMG_filtrada= zeros(length(EMG_rectificada_Q),1);



%Bucle for
%Versión 1
for k=1:1:fin-N
    acumulado=0;
    for j=0+k:1:N+k
        dataIn=EMG_rectificada_Q(j);
        acumulado = quantize(Q_suma, acumulado + dataIn);
    end
    EMG_filtrada(k) = quantize(Q_data, acumulado/N);
end

EMG_filtrada_fin = EMG_filtrada(1:fin-N);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Cálculo de errores

% %Error absoluto medio
MAE1= sum(abs(EMG_Normalizada - EMG_Q))/length(EMG_Normalizada);
MAE2= sum(abs(EMG_Normalizada - EMG_Q))/length(EMG_Normalizada);
% %Error cuadrático medio
RMSE = sqrt(sum((EMG_Normalizada - EMG_Q).^2)/length(EMG_Normalizada));

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

plot (Tiempo,EMG_rectificada_Q_ini,'g');
legend('EMG original','EMG rectificada');

plot (Tiempo,EMG_filtrada_fin,'r');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;

%1) Datos normalizados de la señal EMG
%Guardado de datos de la señal EMG normalizados
% data_q = EMG_Q;
% 
% fidir= fopen ('Datain_MM_Q.dat', 'w+');
% 
% for cont_q=1:fin-N
%     sampleh= num2hex(Q_data, (real(data_q(cont_q))));
%     samplei= hex2dec (sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);



% %2) Datos cuantificados
% %Guardado de datos de la señal EMG cuantificada
% data_q = EMG_Q;
% 
% fidir= fopen ('Datain_MM_Q.dat', 'w+');
% fidhr= fopen ('Datain_MM_Q.txt', 'w+');
% for cont_q=1:fin-N
%     sampleh=  real(data_q(cont_q));
%     samplei= sampleh;
%     fprintf (fidhr, '%.9f, ', sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);
% fclose (fidhr);

%3) Datos de salida, EMG filtrada con la Media movil(normalizados)
%Guardado de datos de la señal EMG cuantificada
% dataout = EMG_filtrada_fin;
% 
% fidir= fopen ('Dataout_MM_Q.dat', 'w+');
% 
% for cont_f=1:fin-N
%     sampleh= num2hex(Q_data, (real(dataout(cont_f))));
%     samplei= hex2dec (sampleh);
%     fwrite (fidir, samplei, 'int32');
% end
% fclose (fidir);





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Guardado de datos de entrada de la señal EMG cuantificada
% datain = EMG;
% Q_in = Q_data;
% qdatain= EMG_Q;

% fidir= fopen ('Datain_EMG_cuantificada.dat', 'w+');
% fidhr= fopen ('Datain_EMG_cuantificada.txt', 'w+');
% for cont=1:length(datain),
% sampleh= num2hex(Q_in, real(qdatain(cont)));
% samplei= hex2dec(sampleh);
% fprintf (fidhr, 'x"%s" ', sampleh);
% fwrite (fidir, samplei, 'int32');
% end;
% fclose (fidir);
% fclose (fidhr);
% 
% %Guardado de datos de salida de la señal EMG
% dataout = EMG_filtrada;
% Q_in = Q_data;
% qdatain= EMG_Q;
% 
% fidir= fopen ('Dataout_Media_Movil.dat', 'w+');
% fidhr= fopen ('Dataout_Media_Movil.txt', 'w+');
% for cont=1:length(dataout),
% sampleh= num2hex(Q_in, real(qdatain(cont)));
% samplei= hex2dec(sampleh);
% fprintf (fidhr, 'x"%s" ', sampleh);
% fwrite (fidir, samplei, 'int32');
% end;
% fclose (fidir);
% fclose (fidhr);
