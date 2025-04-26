Please include your answers to the questions below with your submission, entering into the space below each question
See [Mastering Markdown](https://guides.github.com/features/mastering-markdown/) for github markdown formatting if desired.

*Be sure to take measurements with logging disabled to ensure your logging logic is not impacting current/time measurements.*

*Please include screenshots of the profiler window detailing each current measurement captured.  See the file Instructions to add screenshots in assignment.docx in the ECEN 5823 Student Public Folder.*

1. Provide screen shot verifying the Advertising period matches the values required for the assignment.
   ANSWER : 250.50ms
   <br>Screenshot:  
   ![](image-40.png)

2. What is the average current between advertisements - i.e. when the MCU is sleeping in EM2. (Don't measure an interval with a LETIMER UF event)?
   Answer: 6.65UA
   <br>Screenshot:  
   ![](image-41.png)

3. What is the peak current of an advertisement? 
   Answer:27.16mA
   <br>Screenshot:  
   ![](image-34.png)

4. Provide screen shot showing the connection interval setting. Does the connection interval match the values you requested in your slave(server) code, or the master's(client) values?.
   ANSWER: slave requested for 75ms interval, 4 latency ,750ms as timeout
           my phone as a client accepted for 45ms interval, 0 latency and 50ms timeout 
   ![](image-36.png)
   ![](image-39.png)

5. What is the average current between connection intervals - i.e. when the MCU is sleeping in EM2. (Don't measure an interval with a LETIMER UF event)?
   Answer:8.92uA
   <br>Screenshot:  
![](image-42.png)

6. If possible, provide screen shot verifying the slave latency matches what was reported when you logged the values from event = gecko_evt_le_connection_parameters_id. 
   <br>Screenshot:  
   ![](image-38.png)

