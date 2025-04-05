#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// Database to store EMI records
class Database {
private:
    int EMI_no;
    float principal_EMI;
    float interest_EMI;
    float total_EMI;
    string EMI_date;
    float principal_Remaining;

public:
    Database() {}

    Database(int emi_no, float principal_emi, float interest_emi, float total_emi, string emi_date, float principal_remaining) {
        EMI_no = emi_no;
        principal_EMI = principal_emi;
        interest_EMI = interest_emi;
        total_EMI = total_emi;
        EMI_date = emi_date;
        principal_Remaining = principal_remaining;
    }

    int getEMI() { return EMI_no; }
    float getPrincipalEMI() { return principal_EMI; }
    float getInterestEMI() { return interest_EMI; }
    float getTotalEMI() { return total_EMI; }
    string getEMIDate() { return EMI_date; }
    float getPrincipalRemaining() { return principal_Remaining; }
};

// EMI Calculator class
class EMICalculator {
private:
    string returnMonthString(string startmonth) {
        if (startmonth == "January") return "Jan";
        else if (startmonth == "February") return "Feb";
        else if (startmonth == "March") return "Mar";
        else if (startmonth == "April") return "Apr";
        else if (startmonth == "May") return "May";
        else if (startmonth == "June") return "Jun";
        else if (startmonth == "July") return "Jul";
        else if (startmonth == "August") return "Aug";
        else if (startmonth == "September") return "Sep";
        else if (startmonth == "October") return "Oct";
        else if (startmonth == "November") return "Nov";
        else return "Dec";
    }

    string returnNextMonth(string currMonth) {
        if (currMonth == "Jan") return "Feb";
        else if (currMonth == "Feb") return "Mar";
        else if (currMonth == "Mar") return "Apr";
        else if (currMonth == "Apr") return "May";
        else if (currMonth == "May") return "Jun";
        else if (currMonth == "Jun") return "Jul";
        else if (currMonth == "Jul") return "Aug";
        else if (currMonth == "Aug") return "Sep";
        else if (currMonth == "Sep") return "Oct";
        else if (currMonth == "Oct") return "Nov";
        else if (currMonth == "Nov") return "Dec";
        else return "Jan";
    }

public:
    // Function to calculate EMI
    float emi_calc(float p, float r, float n) {
        float emi;
        r = r / (12 * 100);  // Monthly interest rate
        emi = (p * r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
        return emi;
    }

    // Generate EMI breakup and store in database
    void calculateAndStore(Database db[], float amount, float rate, int tenure, string startMonth, int startYear) {
        float monthlyEMI = emi_calc(amount, rate, tenure);
        float remainingPrincipal = amount;
        string month = returnMonthString(startMonth);
        int year = startYear;

        for (int i = 0; i < tenure; i++) {
            float interestPart = remainingPrincipal * (rate / (12 * 100));
            float principalPart = monthlyEMI - interestPart;
            remainingPrincipal -= principalPart;

            if (remainingPrincipal < 0) remainingPrincipal = 0;

            string emiDate = month + " " + to_string(year);

            db[i] = Database(i + 1, principalPart, interestPart, monthlyEMI, emiDate, remainingPrincipal);

            month = returnNextMonth(month);
            if (month == "Jan") year++;
        }

        cout << "\nLoan creation date: " << startMonth << " " << startYear << endl;
        cout << "Principal Amount: " << amount << endl;
        cout << "Number of EMIs: " << tenure << endl;
        cout << "Total Payable Amount: " << monthlyEMI * tenure << endl;
        cout << "Monthly EMI: " << monthlyEMI << "\n" << endl;
    }

    // Display EMI breakup
    void printDatabase(Database db[], int n) {
        cout << "EMI Breakdown:\n";
        for (int i = 0; i < n; i++) {
            cout << "EMI No: " << db[i].getEMI()
                 << ", Principal EMI: " << db[i].getPrincipalEMI()
                 << ", Interest EMI: " << db[i].getInterestEMI()
                 << ", Total EMI: " << db[i].getTotalEMI()
                 << ", EMI Date: " << db[i].getEMIDate()
                 << ", Principal Remaining: " << db[i].getPrincipalRemaining()
                 << endl;
        }
    }
};

// MAIN FUNCTION
int main() {
    EMICalculator emiCalc;
    cout << "WELCOME TO NM BANK\n";
    cout << "ENTER THE FOLLOWING DETAILS TO CALCULATE LOAN AND EMI DETAILS:\n";

    float amount, rate;
    int tenure, year;
    string month;

    cout << "Enter the Principal Amount: ";
    cin >> amount;

    cout << "Enter the Rate of Interest (in % per annum): ";
    cin >> rate;

    cout << "Enter the Tenure (in months): ";
    cin >> tenure;

    cout << "Enter Loan Start Month (e.g., January): ";
    cin >> month;

    cout << "Enter Loan Start Year: ";
    cin >> year;

    Database db[100]; // Assuming maximum 100 EMIs

    emiCalc.calculateAndStore(db, amount, rate, tenure, month, year);
    emiCalc.printDatabase(db, tenure);

    return 0;
}
