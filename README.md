# FreeRtos-Communicating-Tasks-Project

## Objectives
This project applies knowledge from the embedded programming part of the course and provides hands-on experience with RTOS concepts such as:
- Tasks
- Timers
- Queues
- Semaphores

## Project Specifications
The project is implemented using FreeRTOS on the target emulation board provided via Eclipse CDT Embedded. The key components include:

1. **Tasks**:
    - Three sender tasks: Two with the same priority and one with a higher priority.
    - One receiver task.

2. **Timers**:
    - Each sender task has an associated timer.
    - The receiver task has its own timer.

3. **Queues**:
    - A single queue is used for communication between the sender and receiver tasks.

4. **Semaphores**:
    - Semaphores are used to synchronize the timers and tasks.

### Task and Timer Behavior
- **Sender Tasks**: Sleep for a random period (`Tsender`), then send a message to the queue. If the queue is full, a counter for blocked messages is incremented.
- **Receiver Task**: Sleeps for a fixed period (`Treceiver`), then checks the queue for messages, processes one message if available, and increments a counter for received messages.
![image](https://github.com/YoussefZidan-0/FreeRtos-Communicating-Tasks-Project/assets/125583818/cd8eafab-948b-41a1-a406-029f2d9716ef)
![image](https://github.com/YoussefZidan-0/FreeRtos-Communicating-Tasks-Project/assets/125583818/16f48fdf-6d16-4804-9382-e3dcb98eb09f)

### Callback Functions
- **Sender Timer Callback**: Unblocks the corresponding sender task by releasing its semaphore.
- **Receiver Timer Callback**: Unblocks the receiver task by releasing its semaphore and periodically resets the system state every 1000 messages.

### Reset Function
This function performs the following:
1. Prints statistics of sent and blocked messages.
2. Resets the counters for messages.
3. Clears the queue.
4. Updates the `Tsender` period to new values from predefined arrays.
5. Destroys timers and stops execution when all values are used.

## Results
- The project collects and plots the number of sent, received, and blocked messages as functions of the average sender timer period.
- Comparisons are made with different queue sizes (3 and 10).

## Documentation
The project documentation includes:
1. **System Design**: Illustrates the overall flow of the program, task communication, and synchronization.
2. **Results**: Contains graphs and interpretation of the data collected during the execution.
3. **References**: Lists any references used.

## Authors
- [Youssef Zidan](link-to-profile)
- [Student2 Name](link-to-profile)

