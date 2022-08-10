hc06 = bluetooth("HC-06", 1);
%%
switcher = 0;
LMT86Temperature = 0;
LMT86TemperatureString = "";
DHTHumidityString = "";
SoilMoistString = "";
maxTime = 120;

temperatures = zeros(1,maxTime);
moisture = zeros(1,maxTime);
humidity = zeros(1,maxTime);

time = zeros(1,maxTime);
counter = 1;
while time(maxTime) == 0
    time(counter) = counter;
    counter = counter + 1;
end

counter = maxTime;

figure

while 1

    tempChar =  read(hc06, 1, "string");

    if tempChar == "L"
        switcher = 1;

        counter = maxTime;
        subplot(3,1,1);
        plot(time, temperatures, 'LineWidth', 3.0);
        ylim([20 30]);
        title("Temperature (Celsius) vs Time");
        xlabel("Time (x Seconds Ago)");
        ylabel("Temperature (Celsius)");
        drawnow();
        while counter ~= 1
            temperatures(counter) = temperatures(counter-1);
            counter = counter - 1;
        end      

        temperatures(1) = str2double(LMT86TemperatureString);
        counter = maxTime;
        LMT86TemperatureString = "";

    elseif tempChar == "D"
        switcher = 2;

        counter = maxTime;
        subplot(3,1,2);
        plot(time, humidity, 'LineWidth', 3.0);
        ylim([0 100]);
        title("Relative Humidity vs Time");
        xlabel("Time (x Seconds Ago)");
        ylabel("Relative Humidity (%)");
        drawnow();
        while counter ~= 1
            humidity(counter) = humidity(counter-1);
            counter = counter - 1;
        end

        humidity(1) = str2double(DHTHumidityString);
        counter = maxTime;
        DHTHumidityString = "";

    elseif tempChar == "H"
        switcher = 3;
        
        counter = maxTime;
        subplot(3,1,3);
        plot(time, moisture, 'LineWidth', 3.0);
        ylim([0 100]);
        title("Moisture Levels vs Time");
        xlabel("Time (x Seconds Ago)");
        ylabel("Moisture (%)");        
        drawnow();
        while counter ~= 1
            moisture(counter) = moisture(counter-1);
            counter = counter - 1;
        end

        moisture(1) = str2double(SoilMoistString);
        counter = maxTime;
        SoilMoistString = "";

    end 

    if switcher == 1 && tempChar ~= "L"
        LMT86TemperatureString = append(LMT86TemperatureString, tempChar);
        
    elseif switcher == 2 && tempChar ~= "D"
        DHTHumidityString = append(DHTHumidityString, tempChar);

    elseif switcher == 3 && tempChar ~= "H"
        SoilMoistString = strcat(SoilMoistString, tempChar);  

    end
end
%%
test = "5";
notest = "4";
comb = test + notest;
%%
z = rand(1,50);
time = zeros(1,50);
counter = 1;
while time(50) == 0
    time(counter) = counter;
    counter = counter + 1;
end
%%
plot(time, z);
counter = 50;
figure
while 1
    plot(time, z);
    ylim([-2 2]);
    drawnow();
    while counter ~= 1
        z(counter) = z(counter-1);
        counter = counter - 1;
    end
    counter = 50;
    z(1) = random('normal', 0.5, 0.5);
    pause(1);
end