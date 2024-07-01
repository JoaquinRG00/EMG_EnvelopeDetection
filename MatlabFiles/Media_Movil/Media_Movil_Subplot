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
N1 = 8;
N2 = 16;
N3 = 32;
N4 = 64;
%Variables para el bucle for
EMG_rectificada1 = [zeros(N1,1); EMG_rectificada_ini];
EMG_rectificada2 = [zeros(N2,1); EMG_rectificada_ini];
EMG_rectificada3 = [zeros(N3,1); EMG_rectificada_ini];
EMG_rectificada4 = [zeros(N4,1); EMG_rectificada_ini];
fin1 = length(EMG_rectificada1);
fin2 = length(EMG_rectificada2);
fin3 = length(EMG_rectificada3);
fin4 = length(EMG_rectificada4);
EMG_filtrada1= zeros(length(EMG_rectificada1),1);
EMG_filtrada2= zeros(length(EMG_rectificada2),1);
EMG_filtrada3= zeros(length(EMG_rectificada3),1);
EMG_filtrada4= zeros(length(EMG_rectificada4),1);

% Bucle for1
for k1=1:1:fin1-N1
    acumulado1=0;
    for j1=0+k1:1:N1+k1
        acumulado1 = acumulado1 + EMG_rectificada1(j1);
    end
    EMG_filtrada1(k1)= acumulado1/N1;
end
EMG_filtrada_fin1 = EMG_filtrada1(1:fin1-N1);

% Bucle for2
for k2=1:1:fin2-N2
    acumulado2=0;
    for j2=0+k2:1:N2+k2
        acumulado2 = acumulado2 + EMG_rectificada2(j2);
    end
    EMG_filtrada2(k2)= acumulado2/N2;
end
EMG_filtrada_fin2 = EMG_filtrada2(1:fin2-N2);

% Bucle for3
for k3=1:1:fin3-N3
    acumulado3=0;
    for j3=0+k3:1:N3+k3
        acumulado3 = acumulado3 + EMG_rectificada3(j3);
    end
    EMG_filtrada3(k3)= acumulado3/N3;
end

EMG_filtrada_fin3 = EMG_filtrada3(1:fin3-N3);

% Bucle for4
for k4=1:1:fin4-N4
    acumulado4=0;
    for j4=0+k4:1:N4+k4
        acumulado4 = acumulado4 + EMG_rectificada4(j4);
    end
    EMG_filtrada4(k4)= acumulado4/N4;
end
EMG_filtrada_fin4 = EMG_filtrada4(1:fin4-N4);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Representación gráfica de la señal EMG sacada de la base de datos
close all;
figure (1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Representacion grafica de la señal EMG sacada de la base de datos
close all;
%Subplot1
subplot(2, 2, 1); % 2 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title('Media Móvil(Ventana de 8 muestras)');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG);%Graficar la señal EMG original
plot (Tiempo,EMG_rectificada_ini,'g');
plot (Tiempo,EMG_filtrada_fin1,'r');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;

%Subplot2
subplot(2, 2, 2); % 2 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title('Media Móvil(Ventana de 16 muestras)');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG);%Graficar la señal EMG original
plot (Tiempo,EMG_rectificada_ini,'g');
plot (Tiempo,EMG_filtrada_fin2,'r');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;


%Subplot3
subplot(2, 2, 3); % 2 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title('Media Móvil(Ventana de 32 muestras)');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG);%Graficar la señal EMG original
plot (Tiempo,EMG_rectificada_ini,'g');
plot (Tiempo,EMG_filtrada_fin3,'r');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;

%Subplot4
subplot(2, 2, 4); % 2 filas, 2 columnas, posición 1
hold on; % Comando para representar varias figuras en una misma ventana
title('Media Móvil(Ventana de 64 muestras)');%Titulo de la gráfica
xlabel('Tiempo'); % titulo del eje x
ylabel('EMG');
plot (Tiempo,EMG);%Graficar la señal EMG original
plot (Tiempo,EMG_rectificada_ini,'g');
plot (Tiempo,EMG_filtrada_fin4,'r');
legend('EMG original','EMG rectificada','EMG filtrada');
hold off;
