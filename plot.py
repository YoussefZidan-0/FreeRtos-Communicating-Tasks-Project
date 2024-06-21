import pandas as pd
import matplotlib.pyplot as plt

# Load the data from the CSV file/*
data = pd.read_csv('freertos_log.csv')

# Extract relevant columns
iterations = data['Iteration']
avg_tsender = data['Avg_Tsender']
total_sent = data['Total_Successful_Messages']
total_blocked = data['Total_Blocked_Messages']
sent1 = data['Sent1']
blocked1 = data['Blocked1']
sent2 = data['Sent2']
blocked2 = data['Blocked2']
sent3 = data['Sent3']
blocked3 = data['Blocked3']

# Plot total sent messages as function of average sender timer period
plt.figure(figsize=(10, 6))
plt.plot(avg_tsender, total_sent, marker='o', label='Total Sent Messages')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Total Sent Messages')
plt.title('Total Sent Messages vs. Average Sender Timer Period')
plt.legend()
plt.grid(True)
plt.show()

# Plot total blocked messages as function of average sender timer period
plt.figure(figsize=(10, 6))
plt.plot(avg_tsender, total_blocked, marker='o', label='Total Blocked Messages', color='red')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Total Blocked Messages')
plt.title('Total Blocked Messages vs. Average Sender Timer Period')
plt.legend()
plt.grid(True)
plt.show()

# Plot sent and blocked messages for high priority sender task (Sender3)
plt.figure(figsize=(10, 6))
plt.plot(avg_tsender, sent3, marker='o', label='High Priority Sent Messages (Sender3)')
plt.plot(avg_tsender, blocked3, marker='o', label='High Priority Blocked Messages (Sender3)', color='red')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Messages')
plt.title('High Priority Sender (Sender3) Messages vs. Average Sender Timer Period')
plt.legend()
plt.grid(True)
plt.show()

# Plot sent and blocked messages for lower priority sender tasks (Sender1 and Sender2)
plt.figure(figsize=(10, 6))
plt.plot(avg_tsender, sent1, marker='o', label='Low Priority Sent Messages (Sender1)')
plt.plot(avg_tsender, blocked1, marker='o', label='Low Priority Blocked Messages (Sender1)', color='red')
plt.plot(avg_tsender, sent2, marker='o', label='Low Priority Sent Messages (Sender2)', linestyle='--')
plt.plot(avg_tsender, blocked2, marker='o', label='Low Priority Blocked Messages (Sender2)', color='red', linestyle='--')
plt.xlabel('Average Sender Timer Period (ms)')
plt.ylabel('Messages')
plt.title('Low Priority Senders (Sender1 and Sender2) Messages vs. Average Sender Timer Period')
plt.legend()
plt.grid(True)
plt.show()
