#ifndef DRIVERKEYBOARD_H
#define DRIVERKEYBOARD_H 
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

const char *char_map[] = {
    0,
    "<ESC>",
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<BACK>",
    "<TAB>", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "´", "[", "<ENTER>",
    "<CTRL>", //ctrl inferior esquerdo
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "ç", "~",
    "'",
    "<SHIFT>", //shift inferior esquerdo
    "]",
    "z", "x", "c", "v", "b", "n", "m", ",", ".", ";",
    "<SHIFT>", //shift inferior direito
    "*", "<ALT>", " ", "<CAPS>",
    "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
    "<NUM>", "<SCROLL>",
    "7", "8", "9",
    "-",
    "4", "5", "6", "+",
    "1", "2", "3", "0", ",",
    "<PrtSc>", 0, "\\", "<F11>", "<F12>"};

const char *shift_char_map[] = {
    0,
    "<ESC>",
    "!", "@", "#", "$", "%", "¨", "&", "*", "(", ")", "_", "+", "<BACK>",
    "<TAB>", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "`", "{", "<ENTER>",
    "<CTRL>", //ctrl inferior esquerdo
    "A", "S", "D", "F", "G", "H", "J", "K", "L", "Ç", "^",
    "\"",
    "<SHIFT>", //shift inferior esquerdo
    "}",
    "Z", "X", "C", "V", "B", "N", "M", "<", ">", ":",
    "<SHIFT>", //shift inferior direito
    "*", "<ALT>", " ", "<CAPS>",
    "<MUTE>", "<VolDown>", "<VolUp>", "<MuteMic>", "<Reload>", "<Sleep>", "<PlaneMode>", "<NoCam>", "<Lock>", "<NaoSei>",
    "<NUM>", "<SCROLL>",
    "<HOME>", "<UP>", "<PgUp>", "-",
    "<LEFT>", "<END>", "<RIGHT>", "+",
    "<END>", "<DOWN>", "<PgDown>", "<INSERT>", "<DEL>",
    "<PrtSc>", 0, "|", "<BrightDown>", "<BrightUp>"};

const char *caps_char_map[] = {
    0,
    "<ESC>",
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "<BACK>",
    "<TAB>", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "´", "[", "<ENTER>",
    "<CTRL>", //ctrl inferior esquerdo
    "A", "S", "D", "F", "G", "H", "J", "K", "L", "Ç", "~",
    "'",
    "<SHIFT>", //shift inferior esquerdo
    "]",
    "Z", "X", "C", "V", "B", "N", "M", ",", ".", ";",
    "<SHIFT>", //shift inferior direito
    "*", "<ALT>", " ", "<CAPS>",
    "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
    "<NUM>", "<SCROLL>",
    "7", "8", "9",
    "-",
    "4", "5", "6", "+",
    "1", "2", "3", "0", ",",
    "<PrtSc>", 0, "\\", "<F11>", "<F12>"};

const char *shift_caps_char_map[] = {
    0,
    "<ESC>",
    "!", "@", "#", "$", "%", "¨", "&", "*", "(", ")", "_", "+", "<BACK>",
    "<TAB>", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "`", "{", "<ENTER>",
    "<CTRL>", //ctrl inferior esquerdo
    "a", "s", "d", "f", "g", "h", "j", "k", "l", "ç", "^",
    "\"",
    "<SHIFT>", //shift inferior esquerdo
    "}",
    "z", "x", "c", "v", "b", "n", "m", "<", ">", ":",
    "<SHIFT>", //shift inferior direito
    "*", "<ALT>", " ", "<CAPS>",
    "<MUTE>", "<VolDown>", "<VolUp>", "<MuteMic>", "<Reload>", "<Sleep>", "<PlaneMode>", "<NoCam>", "<Lock>", "<NaoSei>",
    "<NUM>", "<SCROLL>",
    "<HOME>", "<UP>", "<PgUp>", "-",
    "<LEFT>", "<END>", "<RIGHT>", "+",
    "<END>", "<DOWN>", "<PgDown>", "<INSERT>", "<DEL>",
    "<PrtSc>", 0, "|", "<BrightDown>", "<BrightUp>"};

 class Keyboard{
    public:
        Keyboard(){
            shift = false;
            caps = false;
            posBuffer = 0;
            lenBuffer = 0;
            buffer[0] = (char) '';
        }

        const char* defineChar(int numero){

            if (numero == 170 || numero == 182)
            {
                shift = false;
            }
            else if (numero < 89)
            {
                if (!shift && !caps)
                {
                    if (numero == 42 || numero == 54)
                        shift = true;
                    else if (numero == 58)
                        caps = true;
                    else
                        return char_map[numero];
                }
                else if (caps)
                    if (numero == 58)
                        caps = false;
                    else if (shift)
                        return caps_char_map[numero];
                    else
                        return shift_caps_char_map[numero];
                else if (shift)
                    return shift_char_map[numero];
            }

            return "";
        }

        size_t attBuffer(int numero){
            char* novaLetra = defineChar(numero);
            size_t tam = strlen(novaLetra);
            size_t um = strlen("A");
            if(tam == 1){
                if(posBuffer == lenBuffer){
                    buffer[posBuffer] = novaLetra;
                    posBuffer++;
                    lenBuffer++;
                }else{
                    for (size_t i = posBuffer; i < lenBuffer+um; i++)
                    {
                        buffer[i+1] = buffer[i];
                    }
                    buffer[posBuffer] = novaLetra;
                    lenBuffer++;
                    posBuffer++;
                }
                return 1;
            }else if(novaLetra ==  "<BACK>")
            {
                if(posBuffer == lenBuffer){
                    buffer[posBuffer] = "";
                    posBuffer--;
                    lenBuffer--;
                }else{
                    for (size_t i = posBuffer; i < lenBuffer; i++)
                    {
                        buffer[i] = buffer[i+1];
                    }
                    buffer[lenBuffer] = "";
                    lenBuffer--;
                    posBuffer--;
                }
                return 1;
            }
            else if (novaLetra ==  "<ENTER>")
            {
                return 2;
            }
            return 0;
            
            
        }

    public:
        char buffer[80];
        bool shift, caps;
        int posBuffer, lenBuffer;
};



#endif
