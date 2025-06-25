#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Task {
public:
    string title;
    string category;
    bool isCompleted;

    Task(string t, string c = "General", bool comp = false) {
        title = t;
        category = c;
        isCompleted = comp;
    }
};

vector<Task> tasks;

void addTask() {
    string title, category;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter category (e.g., Work, Personal): ";
    getline(cin, category);
    tasks.push_back(Task(title, category));
    cout << "Task added.\n";
}

void viewTasks(bool showCompleted) {
    cout << (showCompleted ? "\nCompleted Tasks:\n" : "\nPending Tasks:\n");
    int count = 0;
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].isCompleted == showCompleted) {
            cout << i + 1 << ". [" << tasks[i].category << "] " << tasks[i].title << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "No " << (showCompleted ? "completed" : "pending") << " tasks.\n";
}

void markAsCompleted() {
    viewTasks(false);
    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;
    if (index >= 1 && index <= tasks.size() && !tasks[index - 1].isCompleted) {
        tasks[index - 1].isCompleted = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void showSummary() {
    int completed = 0, pending = 0;
    for (Task t : tasks) {
        if (t.isCompleted) completed++;
        else pending++;
    }
    cout << "\nSummary:\n";
    cout << "Total: " << tasks.size() << " | ";
    cout << "Pending: " << pending << " | ";
    cout << "Completed: " << completed << "\n";
}

void saveTasksToFile() {
    ofstream out("tasks.txt");
    for (Task t : tasks) {
        out << t.title << "|" << t.category << "|" << t.isCompleted << endl;
    }
    out.close();
    cout << "Tasks saved to file.\n";
}

void loadTasksFromFile() {
    tasks.clear();
    ifstream in("tasks.txt");
    string line;
    while (getline(in, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);
        string title = line.substr(0, first);
        string category = line.substr(first + 1, second - first - 1);
        bool completed = line.substr(second + 1) == "1";
        tasks.push_back(Task(title, category, completed));
    }
    in.close();
}

int main() {
    string input;
    loadTasksFromFile();

    do {
        cout << "\n--- Task Manager ---\n";
        showSummary();
        cout << "\n1. Add Task\n";
        cout << "2. View Pending Tasks\n";
        cout << "3. View Completed Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Save & Exit\n";
        cout << "Enter your choice: ";

        getline(cin, input);

        int choice;
        try {
            choice = stoi(input);  // convert string to integer
        } catch (...) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(false); break;
            case 3: viewTasks(true); break;
            case 4: markAsCompleted(); break;
            case 5: saveTasksToFile(); cout << "Goodbye.\n"; break;
            default: cout << "Invalid option.\n";
        }

    } while (input != "5");

    return 0;
}

