#include <iostream>
#include <string>
#include <vector> // Note: You may not use std::vector or other containers for your stacks.
#include <sstream>


std::vector<std::string> get_args(const std::string& command) {
    std::vector<std::string> args;
    std::stringstream ss(command);
    std::string arg;
    bool in_quotes = false;
    std::string current_arg;

    for (char c : command) {
        if (c == ' ' && !in_quotes) {
            if (!current_arg.empty()) {
                args.push_back(current_arg);
                current_arg.clear();
            }
        } else if (c == '"') {
            in_quotes = !in_quotes;
        } else {
            current_arg += c;
        }
    }
    if (!current_arg.empty()) {
        args.push_back(current_arg);
    }
    return args;

    struct Node{
        int data;
        int weight;
        int index;
        Node* next;
        Node(int val) : data(val),weight(0),index(0),next(nullptr){}
    };
}
class Stack{
    private:
        Node* top_stack;
        Node* bot_stack;
        int total_weight;
    public:
        void print();
        void push();
        int pop();
        void push(Node *n){
            if(!bottom){
                bottom = n;
            }
            n->next=top;
            top=n;
            totalWeight+=n->weight;
        }
        Node* pop(){
            if(!top){
                return nullptr;
            }
            Node *n = top;
            top = top->next;
            totalWeight-=n->weight;
            delete top;
            return top;
         }
        void print() const{
            Node *n = head;
            while (n){
                cout<< n->data;
                if(n->next){
                    std::cout << " ";
                n = n->next;
                }
            }
        }
        bool isEmpty(){
            top == nullptr;
            return top;
        }

};

int main() {
    int max_weight=0;
    std::string initial_string = "";

    std::string line;
    int weight;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> args = get_args(line);
        std::string command = args[0];

        // Example of how to handle a command
        if (command == "PRINT") {
            std::cout<< initial_tring << std::endl;
        }
        else if (command == "CREATE"){
            max_weight = std::stoi(args[1]);
            initial_string = args[2];
            std::cout << "CREATE" + max_weight + "This is the initial text";
        }
        else if (command == "APPEND"){
            std::string string_to_append= args[1];
            initial_string += string_to_append;
            std::cout << "APPEND" + initial_string;
        }
        //args[0]="REPLACE" args[1]="t" args[2]= "T"
        else if (command == "REPLACE"){
            char find_char= args[0][1];
            char replace_char = args[0][2];
            int count=0;
            for(char& c : initial_string){
                if(c==find_char){
                    c=replace_char;
                    count++;
                }
            }
            std::cout<<"REPLACE" + find_char + " " + replace_char;
        }
        else if(command == "DELETE"){
            int index= stoi(args[1]);
            int count=0;
            std::string new_string = "";
            for (int i=0; i<index;i++){
                new_string+=initial_string[i];
            }
            weight=initial_string.size()-index;        
            initial_string=new_string;
            std::cout<< "Delete" + weight << std::endl;
        }
        else if(command == "UNDO"){
            if(undoStack.isempty()){
                std::cout << "Error: Nothing to undo" << std::endl;
            }
        }
        else if(command == "REDO"){
            if(undoStack.empty()){
                std::cout<< "Error: Nothing to Redo" << std::endl;
            }
        }
        // TODO: Handle other commands: CREATE, APPEND, REPLACE, DELETE, UNDO, REDO
    }

    return 0;
}
