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
}
struct Node{
    std::string data;
    int weight;
    Node* next;
};
class Stack{
    private:
        Node* top;
        int total_weight;
        int max_weight;
        
    public:
        void init(){
            top = nullptr;
            total_weight = 0;
            max_weight=0;
        }
        void push(const std::string&data, int weight){
            Node* n = new Node;
            n->data=data;
            n->weight=weight;
            n->next=top;
            top=n;
            total_weight+=n->weight;

            while (max_weight >0 && total_weight>max_weight){
                removeBottom();
            }
        }
        Node* pop(){
            if(!top){
                return nullptr;
            }
            Node *n = top;
            top = top->next;
            total_weight-=n->weight;
            return n;
         }
        bool isEmpty(){
            if(top==nullptr){
                return true;
            }
            else{
                return false;
            }
        }
        void clear(){
            while (top){
                Node* n = top;
                top=top->next;
                delete n;

            }
            total_weight=0;
        }
    void removeBottom(){
        Node* prev= nullptr;
        Node* curr = top;
        if (!curr){
            return;
        }
        //if only one node
        if(curr->next == nullptr){
            total_weight-=curr->weight;
            delete curr;
            top = nullptr;
            return;
            
        }
        //traveres until it reaches the end;
        while (curr->next!=nullptr){
            prev=curr;
            curr=curr->next;
        }
        total_weight-=curr->weight;
        delete curr;
        prev->next=nullptr;

    }
    void setMaxWeight(int mw){
        max_weight=mw;
    }

};

int main() {
    int max_weight=0;
    std::string initial_string = "";

    Stack undoStack;
    Stack redoStack;

    undoStack.init();
    redoStack.init();

    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> args = get_args(line);
        std::string command = args[0];

        // Example of how to handle a command
        if (command == "PRINT") {
            std::cout<< initial_string << std::endl;
        }
        else if (command == "CREATE"){
            max_weight = std::stoi(args[1]);
            initial_string = args[2];
            undoStack.setMaxWeight(max_weight);
            undoStack.setMaxWeight(max_weight);
            std::cout << "CREATE " << max_weight << " \"" << initial_string << "\"" << std::endl;
        }
        else if (command == "APPEND"){
            std::string string_to_append= "";
            int count=args.size();
            for(int i=1; i<count;i++){
                if(i>1){
                    string_to_append+= " ";
                }
                string_to_append+=args[i];
            }
            int weight = string_to_append.length();
            undoStack.push(initial_string,weight);
            redoStack.clear();
            initial_string += string_to_append;
            std::cout << "APPEND " << initial_string << std::endl;
        }
        else if (command == "REPLACE"){
            char find_char= args[1][0];
            char replace_char = args[2][0];
            int count=0;
            undoStack.push(initial_string,0);
            for(char& c : initial_string){
                if(c==find_char){
                    c=replace_char;
                    count++;
                }
            }
            std::cout<<"REPLACE " << find_char << " " << replace_char << std::endl;
        }
        else if(command == "DELETE"){
            int index= std::stoi(args[1]);
            undoStack.push(initial_string,initial_string.size()-index);
            redoStack.clear();
            initial_string= initial_string.substr(0,index);
            std::cout<< "DELETE " << index << std::endl;
            std::cout<< initial_string <<std::endl;
        }
        else if(command == "UNDO"){
            if(undoStack.isEmpty()){
                std::cout << "Error: Nothing to undo" << std::endl;
            }
            else{
                Node* last_undo = undoStack.pop();
                redoStack.push(initial_string,last_undo->weight);
                initial_string=last_undo->data;
                delete last_undo;
                std::cout << "UNDO " << initial_string << std::endl;
            }
        }
        else if(command == "REDO"){
            if(redoStack.isEmpty()){
                std::cout<< "Error: Nothing to Redo" << std::endl;
            }
            else{
                Node* last_redo=redoStack.pop();
                undoStack.push(initial_string,last_redo->weight);
                initial_string=last_redo->data;
                delete last_redo;
                std::cout<< "REDO " << initial_string << std::endl;
            }
        }
    }

    return 0;
}
