#include "../include/investiments.h"
#include "../include/file.h"
#include "../include/date.h"
#include <iostream>
#include <fstream>
#include <iomanip>


time_t increment_month(time_t current_date)
{
    struct tm date_tm = *localtime(&current_date);
    date_tm.tm_mon += 1;
    date_tm.tm_mday = 1;
    return mktime(&date_tm);
}

float monthly_profit(float amount, float daily_yield, int business_days){
    for (int i = 0; i <= 0; i++)
    {
        amount += (amount * daily_yield);
    }
    
}

float incometaxrate(int &elapsed_days){

    if(elapsed_days <=  180) return 0.225;
    else if(elapsed_days >= 181 && elapsed_days <= 360) return 0.2;
    else if(elapsed_days >= 361 && elapsed_days <= 720) return 0.175;
    else return 0.15;
}


float* Investiment::profit(investiments investiments, std::vector<holidays> holidays)
{
    tm start_date = getnextbusinessday(investiments.starting_date), end_date = getnextbusinessday(investiments.ending_date);
    time_t starting_date = mktime(&start_date);
    int business_days = 0, elapsed_days = 0;
    investiments.rate /= 100;
    float monthly_yield = investiments.rate / 12, daily_yield = 0, amount = investiments.value, earnings = 0, income_tax_rate = 0, income_tax = 0;
    float *money = new float[3]; 
    holidays = filterholidays(starting_date, holidays);
    for (time_t current_date = starting_date; current_date <= investiments.ending_date; current_date = increment_month(current_date))
    {
        struct tm date = *localtime(&current_date);
        business_days = getbusinessdays(date, holidays, elapsed_days);
        if (business_days)
        {
            daily_yield = monthly_yield / business_days;
            for (int i = 0; i < business_days; i++)
            {
                amount+= amount * daily_yield;
                earnings = (amount - investiments.value) * income_tax_rate;
                income_tax += income_tax - (amount - investiments.value) * income_tax_rate;
                //amount -= income_tax;
            }
            
        }

    }


    //dinheiro liquido
    money[0] = amount - amount * incometaxrate(elapsed_days);
    //dinheiro bruto
    money[1] = amount;
    //imposto recolhido na fonte
    money[2] = amount * incometaxrate(elapsed_days);

    return money;
}
float Investiment::roi()
{
    return 0.0f;
}