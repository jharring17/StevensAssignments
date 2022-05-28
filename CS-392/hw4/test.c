 char* array = (char*)malloc(length + 1);
        difference = num;
        array[length] = 0;
        for (i = length - 1; i >= 0; i--) {
            char thisNum = (dif % 10) + '0';
            array[i] = thisNum;
            difference = (difference / 10);
        }
