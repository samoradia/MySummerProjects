//Saagar Moradia
//26 July 2018
//CS106B
//This program will see if all of the patients in a list can be seen by the doctors using backtracking
//Sources
//Lecture Slides 11,12,13

#include "DoctorsWithoutOrders.h"
#include "map.h"
#include <climits>
#include <iostream>
using namespace std;

bool patientHelper(Vector<Doctor> &doctors,
                   Vector<Patient> &patients,
                   Map<string, Set<string>>& schedule, Vector<int>& remHours);
void createVectorDoc(Vector<Doctor> &doctors, Vector<int> &remHours);
void createVectorPat(Vector<Patient> &patients, Vector<int> &patHours);
int sum(const Vector<int> vec);
/* * * * Doctors Without Orders * * * */

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */
bool canAllPatientsBeSeen(Vector<Doctor> &doctors,
                          Vector<Patient> &patients,
                          Map<string, Set<string>>& schedule) {
    Vector<int> remHours;
    Vector<int> patHours;
    Vector<Patient> tempPat = patients;
    createVectorDoc(doctors, remHours);
    createVectorPat(patients, patHours);
    //if more hours needed than availible, always is false
    if(sum(patHours) > sum(remHours)){
        return false;
    }
   return patientHelper(doctors, tempPat, schedule, remHours);
}
/**
 * @brief createVector Given a vector of doctors, it will initialize a vector of ints to the number of hours free for each doctor
 * @param doctors A vector of doctors
 * @param remHours An outparameter that will contain the number of free hours for each doctor
 */
void createVectorDoc(Vector<Doctor> &doctors, Vector<int> &remHours){
    for(int i = 0; i<doctors.size(); i++){
        remHours.add(doctors[i].hoursFree);
    }
}
/**
 * @brief createVectorPat Given a vector of patients, it will initialize a vector of ints to the number of hours needed for each patient
 * @param patients - vector of patients
 * @param patHours - outparameter that will contain the number of hours needed for each patient
 */
void createVectorPat(Vector<Patient> &patients, Vector<int> &patHours){
    for(int i = 0; i<patients.size(); i++){
        patHours.add(patients[i].hoursNeeded);
    }
}
/**
 * @brief sum - finds the sum of the values of a vector
 * @param vec - vector to be summed
 * @return - sum of vector
 */
int sum(const Vector<int> vec){
    int sum = 0;
    for(int i = 0; i<vec.size(); i++){
        sum+=vec[i];
    }
    return sum;
}
/**
 * @brief patientHelper This function will attempt to see if all patients can be seen by the doctors, and if so will
 * input them into a map to be outputted
 * @param doctors - vector of doctor objects
 * @param patients - vector of patient objects
 * @param schedule - outparameter that will show which doctors will see which patients if the schedule is possible
 * @param numPatient - the index of the patient to be seen
 * @param remHours - a vector that contains the number of hours availible for each doctor to be changed
 * @return  - whether or not a schedule was found
 */
bool patientHelper(Vector<Doctor> &doctors,
                   Vector<Patient> &patients,
                   Map<string, Set<string>>& schedule, Vector<int>& remHours){
    if (patients.size() == 0){
        return true;
    } else {
        for (int  i = 0; i < remHours.size(); i++){
            for(int j =0; j< patients.size(); j++){
                if (patients[j].hoursNeeded <= remHours[i]){
                    remHours[i] -= patients[j].hoursNeeded;
                    //take patient out of consideration, but hold value in case combination is false
                    Patient hold = patients[j];
                    patients.remove(j);
                    //only return if true
                    if (patientHelper(doctors, patients,schedule, remHours)){
                        schedule[doctors[i].name].add(hold.name);
                        return true;
                    } else {
                        remHours[i] +=hold.hoursNeeded;
                        patients.add(hold);
                    }
                }
            }
        }
        return false;
    }
}
