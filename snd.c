#include "snd.h"
#include <stdio.h>
#include <string.h>


/**********************************
* read wav file
**********************************/
ulong readSoundFile(const char *path, double *buf, uint samples)
{
    /* open sound file */
    SNDFILE *file = NULL;
    SF_INFO  info;    
    uint items_read = 0;
    memset(&info, 0, sizeof(info));
    
    file = sf_open(path, SFM_READ, &info);
    if (file == NULL)
    {
        fprintf(stderr, "%s: error opening sound file.\n", __FUNCTION__);
        return items_read;
    }
    fprintf(stdout, "%s: successfully opened (sample rate: %d).\n", __FUNCTION__, info.samplerate);
            
    if (info.channels == 1)
    {      
        /* read data */
        items_read = sf_read_double(file, buf, samples);
        if (items_read != samples)
        {
            fprintf(stderr, "%s: only %d samples out of requested %d samples imported.\n", __FUNCTION__, items_read, samples);    
        }
    }
    else
    {
        fprintf(stderr, "%s: can only process files with 1 channel.\n", __FUNCTION__);
    }
    
    /* close sound file */
    sf_close(file);
    return items_read;
}
