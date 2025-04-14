#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

#define INITIAL_CAPACITY 4

ASTNode* create_node(NodeType type, char* text) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    node->type = type;
    node->text = strdup(text);
    node->value = 0;
    node->correct = -1;
    node->answer = -1;
    node->score_condition = -1;
    node->score_value = -1;
    
    node->parent = NULL;
    node->children = (ASTNode**)malloc(INITIAL_CAPACITY * sizeof(ASTNode*));
    if (!node->children) {
        fprintf(stderr, "Memory allocation failed\n");
        free(node);
        exit(1);
    }
    
    node->num_children = 0;
    node->capacity = INITIAL_CAPACITY;
    
    return node;
}

void add_child(ASTNode* parent, ASTNode* child) {
    if (!parent || !child) {
        return;
    }
    
    if (parent->num_children >= parent->capacity) {
        parent->capacity *= 2;
        parent->children = (ASTNode**)realloc(parent->children, parent->capacity * sizeof(ASTNode*));
        if (!parent->children) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(1);
        }
    }
    
    parent->children[parent->num_children++] = child;
    child->parent = parent;
}

void free_node(ASTNode* node) {
    if (!node) {
        return;
    }
    
    for (int i = 0; i < node->num_children; i++) {
        free_node(node->children[i]);
    }
    
    free(node->text);
    free(node->children);
    free(node);
}

void print_ast(ASTNode* node, int level) {
    if (!node) {
        return;
    }
    
    /* Print indentation */
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    
    /* Print node info based on type */
    switch (node->type) {
        case NODE_ASSESSMENT:
            printf("ASSESSMENT: %s\n", node->text);
            break;
        case NODE_SECTIONS:
            printf("SECTIONS\n");
            break;
        case NODE_SECTION:
            printf("SECTION: %s\n", node->text);
            break;
        case NODE_QUESTIONS:
            printf("QUESTIONS\n");
            break;
        case NODE_MC_QUESTION:
            printf("MC_QUESTION: %s\n", node->text);
            break;
        case NODE_TF_QUESTION:
            printf("TF_QUESTION: %s\n", node->text);
            break;
        case NODE_OPTION:
            printf("OPTION: %s (%s)\n", node->text, node->correct ? "CORRECT" : "INCORRECT");
            break;
        case NODE_ANSWER:
            printf("ANSWER: %s\n", node->text);
            break;
        case NODE_FEEDBACK:
            printf("FEEDBACK: %s\n", node->text);
            break;
        case NODE_IF_SCORE:
            printf("IF_SCORE: %s %d\n", 
                   node->score_condition ? "ABOVE" : "BELOW", 
                   node->score_value);
            break;
        default:
            printf("UNKNOWN NODE\n");
    }
    
    /* Print children recursively */
    for (int i = 0; i < node->num_children; i++) {
        print_ast(node->children[i], level + 1);
    }
}