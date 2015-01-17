#include "snd.h"
#include <stdio.h>
#include <string.h>


/**********************************
* read wav file
**********************************/
uint readSoundFile(const char *path, double *buf, uint samples)
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
        fprintf(stderr, "%s: got %u samples.\n", __FUNCTION__, items_read);          
    }
    else
    {
        fprintf(stderr, "%s: can only process files with 1 channel.\n", __FUNCTION__);
    }
    
    /* close sound file */
    sf_close(file);
    return items_read;
}


/**********************************
* write wav file
**********************************/
uint writeSoundFile(const char *path, double *data, uint samples, uint samplerate, uint repeat)
{
    /* open sound file */
    SNDFILE *file = NULL;
    SF_INFO  info;    
    uint items_written = 0, i;
    memset(&info, 0, sizeof(info));
    
    /* set header */
    info.samplerate = samplerate;
    info.channels = 1;
    info.format = SF_FORMAT_WAV|SF_FORMAT_PCM_16;    
    
    /* open */
    file = sf_open(path, SFM_WRITE, &info);
    if (file == NULL)
    {
        fprintf(stderr, "%s: error writing sound file.\n", __FUNCTION__);
        return items_written;
    }
    fprintf(stdout, "%s: successfully opened (sample rate: %d).\n", __FUNCTION__, info.samplerate);
                 
    /* read data */
    for (i = 0; i < repeat; ++i)
    {
        items_written += sf_write_double(file, data, samples);
    }
    fprintf(stderr, "%s: wrote %u samples.\n", __FUNCTION__, items_written);          
       
    /* close sound file */
    sf_close(file);
    return items_written;
}
