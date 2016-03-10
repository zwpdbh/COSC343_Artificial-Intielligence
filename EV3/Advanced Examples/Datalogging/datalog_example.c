/*---------------------------------------------------------------------------*/
/*        Module:     Datalog_example.c                                      */
/*        Author:     James Pearman                                          */
/*        Created:    12 Nov 2015                                            */
/*        Platform:   Vex-IQ, EV3, NXT                                       */
/*        RC Version: 4.51                                                   */
/*                                                                           */
/*        Revisions:                                                         */
/*                    1.00  12 Nov 2015 - Initial release                    */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description:                                                       */
/*                                                                           */
/*        This sample code demonstrates the use of dataloging commands       */
/*---------------------------------------------------------------------------*/
/*                                                                           */

#if defined(VexIQ) || defined(EV3) || defined(NXT) || defined(VEX2)

// Global variables used by the sample code
int   global_1 = 0;
int   global_2 = 0;
int   global_3 = 0;

// We have 8 possible places to store data, we call each one a datalog series
// This example uses the first three to store values.
#define   DATALOG_SERIES_0    0
#define   DATALOG_SERIES_1    1
#define   DATALOG_SERIES_2    2

/*---------------------------------------------------------------------------*/
task main()
{
    int loops = 0;

    // Clear old data
    datalogClear();

    while(1)
        {
        // datalogAddValue adds one row to the datalog but does not time stamp the value
        datalogAddValue( DATALOG_SERIES_0, loops++ );


        // datalogAddValue when surrounded by datalogDataGroupStart and datalogDataGroupEnd
        // adds several values to one row of the datalog with a common time stamp
        datalogDataGroupStart();
        datalogAddValue( DATALOG_SERIES_0, global_1++ );
        datalogAddValue( DATALOG_SERIES_1, global_2++ );
        datalogAddValue( DATALOG_SERIES_2, global_3++ );
        datalogDataGroupEnd();

        // datalogAddValueWithTimeStamp adds one row that is time stamped
        // the following statement is equivalent to the code
        //
        // datalogDataGroupStart();
        // datalogAddValue( DATALOG_SERIES_0, global_1++ );
        // datalogDataGroupEnd();
        //
        datalogAddValueWithTimeStamp( DATALOG_SERIES_0, global_1++ );



        // More examples of datalogAddValueWithTimeStamp
        // The small delay is just for demonstration purposes
        wait1Msec(10);
        datalogAddValueWithTimeStamp( DATALOG_SERIES_1, global_2++ );
        wait1Msec(10);
        datalogAddValueWithTimeStamp( DATALOG_SERIES_2, global_3++ );

        // loop delay
        wait1Msec(50);
        }
}

/*---------------------------------------------------------------------------*/
#else
#warning "Invalid platform selected for this sample program"
#endif
