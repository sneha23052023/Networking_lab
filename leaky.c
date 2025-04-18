#include <stdio.h>
#include <stdlib.h>

int main()
{
    int outgoing = 0, bucket_size, store = 0, n, pack_loss, i;
    
    printf("Enter the bucket size: ");
    scanf("%d", &bucket_size);
    
    printf("Enter the number of inputs: ");
    scanf("%d", &n);
    
    int in_packets[n];
    
    printf("Enter the incoming packet size:\n");
    for (i = 0; i < n; i++) 
    {
        scanf("%d", &in_packets[i]);
    }

    for (i = 0; i < n; i++)
     {
        outgoing += in_packets[i];
    }

    outgoing = outgoing / n;

    printf("The average outgoing rate of packets: %d\n", outgoing);

    for (i = 0; i < n; i++) {
        printf("Incoming packet size: %d\n", in_packets[i]);
        
        if (in_packets[i] <= (bucket_size - store)) {
            store += in_packets[i];
            printf("Bucket status: %d out of %d\n", store, bucket_size);
        } else
         {
            pack_loss = in_packets[i] - (bucket_size - store);
            printf("Dropped number of packets: %d\n", pack_loss);
            store = bucket_size;
            printf("Bucket status: %d out of %d\n", store, bucket_size);
        }

        store -= outgoing;

        if (store < 0)
         {
            store = 0;
        }

        printf("After outgoing: Bucket status: %d out of %d\n\n", store, bucket_size);
    }

    return 0;
}