#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct TelemetryData
{
    long timestamp_ms;
    int motor1_pwm, motor2_pwm, motor3_pwm, motor4_pwm;
    float pitch_deg, roll_deg, yaw_deg;
};

int main()
{
    ifstream inputFile("data/telemetry.csv");
    if (!inputFile)
    {
        cerr << "Error: file can not be opened.";
        return 1;
    }
    string line;
    getline(inputFile, line);
    
    vector<TelemetryData> rawLogs;
    rawLogs.reserve(1000);
    while (getline(inputFile, line))
    {
        stringstream dataRow(line);
        TelemetryData rowData;
        string token;

        getline(dataRow, token, ',');
        rowData.timestamp_ms = stol(token);

        getline(dataRow, token, ',');
        rowData.motor1_pwm = stoi(token);
        getline(dataRow, token, ',');
        rowData.motor2_pwm = stoi(token);
        getline(dataRow, token, ',');
        rowData.motor3_pwm = stoi(token);
        getline(dataRow, token, ',');
        rowData.motor4_pwm = stoi(token);

        getline(dataRow, token, ',');
        rowData.pitch_deg = stof(token);
        getline(dataRow, token, ',');
        rowData.roll_deg = stof(token);
        getline(dataRow, token, ',');
        rowData.yaw_deg = stof(token);

        rawLogs.push_back(rowData);
    }
    
    vector<TelemetryData> cleanLogs;
    cleanLogs.reserve(rawLogs.size());

    for (const auto& log : rawLogs)
    {
        if (!(log.motor1_pwm < 1000 || 
                log.motor1_pwm > 2000 ||
                log.motor2_pwm < 1000 ||
                log.motor2_pwm > 2000 ||
                log.motor3_pwm < 1000 ||
                log.motor3_pwm > 2000 ||
                log.motor4_pwm < 1000 ||
                log.motor4_pwm > 2000 ||
                log.pitch_deg > 90 ||
                log.pitch_deg < -90 ||
                log.roll_deg > 90 ||
                log.roll_deg < -90 ||
                log.yaw_deg > 180 ||
                log.yaw_deg < -180))
            cleanLogs.push_back(log);
    }

    ofstream outputFile("data/clean_telemetry.csv");
    if (!outputFile)
    {
        cerr << "Error: clean file can not be created.";
        return 1;
    }

    outputFile << "timestamp_ms,motor1_pwm,motor2_pwm,motor3_pwm,"
               << "motor4_pwm,pitch_deg,roll_deg,yaw_deg\n";

    
    for (const auto& row : cleanLogs)
    {
        outputFile << row.timestamp_ms << ","
                   << row.motor1_pwm << ","
                   << row.motor2_pwm << ","
                   << row.motor3_pwm << ","
                   << row.motor4_pwm << ","
                   << row.pitch_deg << ","
                   << row.roll_deg << ","
                   << row.yaw_deg << "\n";
    }

    cout << "Successfully processed and exported clean data." << endl;
    return 0;
}