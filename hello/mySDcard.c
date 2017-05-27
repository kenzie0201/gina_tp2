#include "mySDcard.h"
/* Buffer size used for the file copy process */
#ifndef CPY_BUFF_SIZE
#define CPY_BUFF_SIZE       2048
#endif

/* String conversion macro */
#define STR_(n)             #n
#define STR(n)              STR_(n)

/* Drive number used for FatFs */
#define DRIVE_NUM           0
#define TASKSTACKSIZE       768
char initFileName[] = "LOG";
char filename[10];
char count = 0;
char countstr[5];
char writing_flag = 0;
/* Variables to keep track of the file copy progress */
unsigned int bytesWritten = 0;
unsigned int filesize = 0;

const char textarray[] = \
"***********************************************************************\n"
"0         1         2         3         4         5         6         7\n"
"01234567890123456789012345678901234567890123456789012345678901234567890\n"
"This is some text to be inserted into the initFileName if there isn't\n"
"already an existing file located on the media.\n"
"If an initFileName already exists, or if the file was already once\n"
"generated, then the initFileName will NOT be modified.\n"
"***********************************************************************\n";
char testing[50] = "\0";
/*Variable required for SD Card R/W*/
FATFS fatfs;
FIL fil;
FRESULT rc;
UINT br, bw;
FILINFO fno;
int i;
void openFile(void){
    bytesWritten = 0;
    filesize = 0;
    count = 0;

    // mount the file system, using logical disk 0.
          rc = f_mount(0, &fatfs);
          if(rc != FR_OK)
          {
              UARTprintf("f_mount error\n");
          }
          else
          {
              UARTprintf("f_mount success!\n");
          }

          /* Try to open the source file */
             //rc = f_open(&fil, initFileName, FA_READ);
             strcpy(filename,"LOG.csv");
             rc = f_stat(filename, &fno);

             UARTprintf("fno: %s\n", fno.fname);
             while (rc != FR_NO_FILE) { // file exist
                  count++;
                  memset(countstr,0,sizeof(countstr));
                  itoa (count, countstr,10);

                  sprintf(filename, "%s(%s).csv", initFileName, countstr);
                  rc = f_stat(filename, &fno);
              }


//             rc = f_open(&fil, filename, FA_CREATE_NEW|FA_READ|FA_WRITE);
//             if (rc != FR_OK) {

                    /* Open file for both reading and writing */
                    rc = f_open(&fil, filename,  FA_CREATE_ALWAYS | FA_WRITE);
                    if (rc != FR_OK) {
                         UARTprintf("Error: \"%s\" could not be created.\n"
                                       "Please check the Getting Started Guide "
                                       "if additional jumpers are necessary.\n",
                                       filename);
                         UARTprintf("Aborting...\n");
                         return 0;
                     }

//             }


}
void writeSD(char *data){


    f_write(&fil, data, strlen(data), &bytesWritten);
    f_sync(&fil); //the same process as f_close function but the file is left opened and can continue read/write/seek operations to the file

    /* Reset the internal file pointer */
 //   f_lseek(&fil, 0);


}
void closeFile(void){

    /* Get the filesize of the source file */
    filesize = f_size(&fil);
    /* Close both initFileName[] and outputfile[] */
    f_close(&fil);
    f_mount(0, NULL);
    UARTprintf("sucessfully closed the file\n",filename);

}
void initSDcard(void){
    // enable the peripherals used
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;
}
