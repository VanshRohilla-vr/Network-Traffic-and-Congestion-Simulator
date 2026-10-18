int selectTrafficMode(int mode, int arrivals, int processing)
{
    int packets = arrivals;

    switch (mode)
    {
        case 1:
            // Low Traffic
            packets = 1;
            break;

        case 2:
            // Heavy Traffic
            packets = processing + 3;
            break;

        case 3:
            // Random Traffic
            if (arrivals > 0)
            {
                packets = rand() % (arrivals + 1);
            }
            else
            {
                packets = 0;
            }
            break;

        default:
            packets = arrivals;
    }

    return packets;
}

