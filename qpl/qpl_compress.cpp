#include <string>
#include <unistd.h>
#include "qpl_compress.h"
#include "qpl/qpl.h"
#include <sys/time.h>

// #define QPL_SUBMIT

int64_t qpl_compress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t level, size_t param, char* workmem) {
    qpl_status status;
    qpl_compression_levels compress_level;
    qpl_job* job = (qpl_job*)workmem;
    compress_level = (qpl_compression_levels)level;

    /* Job Config */
    job->op            = qpl_op_compress;
    job->next_in_ptr   = (unsigned char*)inbuf;
    job->next_out_ptr  = (unsigned char*)outbuf;
    job->available_in  = insize;
    job->available_out = outsize;
    job->flags         = QPL_FLAG_FIRST | QPL_FLAG_DYNAMIC_HUFFMAN | QPL_FLAG_LAST | QPL_FLAG_OMIT_VERIFY;
    // job->flags         = QPL_FLAG_FIRST | QPL_FLAG_LAST | QPL_FLAG_OMIT_VERIFY;
    job->level         = qpl_default_level;

#ifdef QPL_SUBMIT
    status = qpl_submit_job(job);
    if ( status != QPL_STS_OK )
    {
        printf("Error while compression submit occurred. Code:%d\n",status);
        return 0;
    }
    status = qpl_check_job(job);
    while(status == QPL_STS_BEING_PROCESSED)
    {
        usleep(20); // sleep 10us
        status = qpl_check_job(job);
    }
    if ( status != QPL_STS_OK ) 
    {
        printf("Error while compression occurred. Code:%d\n",status);
        return 0;
    }
#else
    status = qpl_execute_job(job);
    if ( status != QPL_STS_OK ) 
    {
        printf("Error while compression occurred. Code:%d\n",status);
        return 0;
    }
    
#endif

    return (int64_t)job->total_out;
}

int64_t qpl_decompress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t level, size_t param, char* workmem) {
    qpl_status status;
    qpl_job* job = (qpl_job*)workmem;

    /* Job Config */
    job->op            = qpl_op_decompress;
    job->next_in_ptr   = (unsigned char*)inbuf;
    job->next_out_ptr  = (unsigned char*)outbuf;
    job->available_in  = insize;
    job->available_out = outsize;
    job->flags         = QPL_FLAG_FIRST | QPL_FLAG_LAST;

#ifdef QPL_SUBMIT
    status = qpl_submit_job(job);
    if ( status != QPL_STS_OK )
    {
        printf("Error while decompression submit occurred. Code:%d\n",status);
        return 0;
    }
    status = qpl_check_job(job);
    while(status == QPL_STS_BEING_PROCESSED)
    {
        usleep(20); // sleep 10us
        status = qpl_check_job(job);
    }
    if ( status != QPL_STS_OK ) 
    {
        printf("Error while decompression occurred. Code:%d\n",status);
        return 0;
    }
#else
    status = qpl_execute_job(job);
    if ( status != QPL_STS_OK ) 
    {
        printf("Error while decompression occurred. Code:%d\n",status);
        return 0;
    }
#endif

    return (int64_t)job->total_out;
}

char* qpl_init(size_t insize, size_t level, size_t path) {
    qpl_status status;
    qpl_path_t qpl_path = (qpl_path_t)path;
    uint32_t   size = 0;

    status = qpl_get_job_size(qpl_path, &size);
    if ( status != QPL_STS_OK )
    {
        printf("An error acquired during QPL job size getting. Code: %d\n", status);
        return NULL;
    }
    qpl_job* job = (qpl_job*)malloc(size);
    status = qpl_init_job(qpl_path, job);
    if ( status != QPL_STS_OK ) 
    {
        printf("An error acquired during QPL job initializing. Code: %d\n", status);
        return NULL;
    }

    return (char *)job;
}


void qpl_deinit(char* workmem) {
    if (!workmem) return;

    qpl_status status;
    qpl_job* job = (qpl_job*)workmem;
    
    status = qpl_fini_job(job);
    if ( status != QPL_STS_OK )
    {
        printf("An error acquired during job finalization.\n");
    }

    free(workmem);

    return;
}

uint32_t op_len = 0;

