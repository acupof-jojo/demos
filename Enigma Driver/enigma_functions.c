#include "enigma.h"
#include <stdio.h>
#include <stdlib.h>

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
    //printf("Enter Message: "); //DELETE
    fgets(msg, 1024, stdin);
    int parse = 0;
    while(msg[parse] != '\n' && msg[parse] != '\0'){
        parse++;
    }

    if(msg[parse] == '\n'){
        msg[parse] = '\0';
    }

    //printf("Message is: %s", msg); //DELETE
    //printf("END"); //DELETE


    
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
    scanf("%s", which_rotors);
    int parse = 0; 
    int rotorCount = 0;
    while(which_rotors[parse] && parse < 4){
        rotorCount++;
        parse++;
    }
    which_rotors[parse] = '\0';
    //printf("rotors: %s\n", which_rotors);
    //printf("num rotors: %d", rotorCount);

    return rotorCount;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
    char in[2];
    scanf("%s", in);
    int numRotations = atoi(in);
    return numRotations;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){
    //printf("Test");
    int parse = 0;
    while(which_rotors[parse]){
        //printf("test: %c\n", which_rotors[parse]);
        char temp[] = {which_rotors[parse]};
        int con = atoi(temp);
        for(int i = 0; i<27; i++){
            encryption_rotors[parse][i] = ROTOR_CONSTANTS[con][i];
        }
        //printf("\nencryptions_rotors[%d] = %sEND", parse, encryption_rotors[parse]);
        parse++;
    }
    //printf("\nencryptions_rotors[0] = %s", encryption_rotors[0]);
    //printf("\nencryptions_rotors[1] = %s", encryption_rotors[1]);

    return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
    //printf("\nhere!");
    int rotor = 0;
    while(encryption_rotors[rotor][0]){
        for(int r = 0; r < rotations; r++){
            char last = encryption_rotors[rotor][25];
            //printf("\nLAST: %c", last);
            for(int i = 25; i > 0; i--){
                encryption_rotors[rotor][i] = encryption_rotors[rotor][i-1];
            }
            encryption_rotors[rotor][0] = last;
        }
        //printf("\nRotated[%d] = %s", rotor, encryption_rotors[rotor]);
        rotor++;
    }

    return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
    int loc = 0;
    int c = 0;
    for(c = 0; msg[c]; c++){//for each character in msg
        char temp = msg[c];
        for(int r = 0; r < num_active_rotors; r++){//for each rotor
            for(int i = 0; i < 26; i++){ //find letter in id array
                if(temp == ROTOR_CONSTANTS[0][i]){
                    loc = i;
                    temp = encryption_rotors[r][loc];
                    break;
                }
            }

        }

        encrypted_msg[c] = temp;
    }
    encrypted_msg[c] = '\0';
    
    return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
    int loc = 0;
    int c = 0;
    for(c = 0; encrypted_msg[c]; c++){ //for all letters
        char temp = encrypted_msg[c];
        for(int r = num_active_rotors - 1; r >= 0; r--){//backwards in each rotor
            for(int i = 0; i < 26; i++){ //find letter
                if(temp == encryption_rotors[r][i]){
                    loc = i;
                    temp = ROTOR_CONSTANTS[0][loc];
                    break;
                }
            }
            
        }
        decrypted_msg[c] = temp;
    }
    decrypted_msg[c] = '\0';

    return;
}


