#ifndef AST_H
#define AST_H

/* Node types for AST */
typedef enum {
    NODE_ASSESSMENT,
    NODE_SECTIONS,
    NODE_SECTION,
    NODE_QUESTIONS,
    NODE_MC_QUESTION,
    NODE_TF_QUESTION,
    NODE_OPTION,
    NODE_ANSWER,
    NODE_FEEDBACK,
    NODE_IF_SCORE
} NodeType;

/* Node structure for AST */
typedef struct ASTNode {
    NodeType type;
    char* text;      /* For storing strings like question text */
    int value;       /* For numerical values */
    int correct;     /* For OPTION (1 for CORRECT, 0 for INCORRECT) */
    int answer;      /* For ANSWER (1 for TRUE, 0 for FALSE) */
    int score_condition; /* For IF_SCORE (1 for ABOVE, 0 for BELOW) */
    int score_value;  /* For IF_SCORE threshold value */
    
    struct ASTNode* parent;
    struct ASTNode** children;
    int num_children;
    int capacity;
} ASTNode;

/* AST operations */
ASTNode* create_node(NodeType type, char* text);
void add_child(ASTNode* parent, ASTNode* child);
void free_node(ASTNode* node);
void print_ast(ASTNode* node, int level);

#endif /* AST_H */