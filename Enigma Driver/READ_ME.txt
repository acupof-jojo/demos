Overview: Encrpyt and Decrypt messages given by the user - rudimentary version of the enigma machine

Language: C

Functions:

void Get_Message(char msg[]):
This method reads a character array from the keyboard and stores it in the parameter msg
Keyboard input is assumed to be entirely uppercase and/or spaces followed by the enter key

int Get_Which_Rotors(char which_rotors[]):
This function reads up to 4 characters from the keyboard - the rotors to be used on the message
These characaters will be only difits 1-8.
The user will press enter when finished
Returns the number of active rotors

int Get_Rotations():
Reads an integer from the keyboard and returns it
This number represents the number of rotations to apply to the encryption rotors
(Input is assumed to be between 0 and 25 inclusive)

void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]):
This function copies the rotors indicated into the encryption_rotors array
Copies the first and third rotors into the encryption rotors array in positions 0 and 1

void Apply_Rotation(int rotations, char encryption_rotors[4][27]):
Rotates the characters in each of the active encryption rotors to the right by x rotations

void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]):
Takes a string msg and applies the enigma machine to encrypt the message

void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]):
Takes a sring and applies the enigma machine to decrypt the message
