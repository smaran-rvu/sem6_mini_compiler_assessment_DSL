#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

int validate_semantics(ASTNode* root) {
    if (!root) {
        printf("Semantic Error: Empty AST\n");
        return 0;
    }
    
    if (root->type != NODE_ASSESSMENT) {
        semantic_error("Root node must be an ASSESSMENT", root);
        return 0;
    }
    
    return validate_assessment(root);
}

int validate_assessment(ASTNode* node) {
    int valid = 1;
    int section_count = 0;
    
    /* Check that there's at least one section */
    for (int i = 0; i < node->num_children; i++) {
        ASTNode* child = node->children[i];
        
        /* Handle sections container */
        if (child->type == NODE_SECTIONS) {
            for (int j = 0; j < child->num_children; j++) {
                ASTNode* section_child = child->children[j];
                if (section_child->type == NODE_SECTION) {
                    section_count++;
                    valid &= validate_section(section_child);
                }
                else if (section_child->type == NODE_IF_SCORE) {
                    valid &= validate_if_score(section_child);
                    
                    /* Count sections inside IF_SCORE blocks */
                    for (int k = 0; k < section_child->num_children; k++) {
                        if (section_child->children[k]->type == NODE_SECTION) {
                            section_count++;
                        }
                    }
                }
            }
        }
    }
    
    if (section_count == 0) {
        semantic_error("Assessment must have at least one section", node);
        valid = 0;
    }
    
    return valid;
}

int validate_section(ASTNode* node) {
    int valid = 1;
    int question_count = 0;
    
    /* Check that there's at least one question */
    for (int i = 0; i < node->num_children; i++) {
        ASTNode* child = node->children[i];
        
        if (child->type == NODE_QUESTIONS) {
            for (int j = 0; j < child->num_children; j++) {
                ASTNode* question = child->children[j];
                if (question->type == NODE_MC_QUESTION) {
                    question_count++;
                    valid &= validate_mc_question(question);
                }
                else if (question->type == NODE_TF_QUESTION) {
                    question_count++;
                    valid &= validate_tf_question(question);
                }
            }
        }
    }
    
    if (question_count == 0) {
        semantic_error("Section must have at least one question", node);
        valid = 0;
    }
    
    return valid;
}

int validate_mc_question(ASTNode* node) {
    int valid = 1;
    int option_count = 0;
    int correct_count = 0;
    
    /* Find options node */
    ASTNode* options_node = NULL;
    for (int i = 0; i < node->num_children; i++) {
        if (node->children[i]->type == NODE_MC_QUESTION) {  /* Options container */
            options_node = node->children[i];
            break;
        }
    }
    
    if (!options_node) {
        semantic_error("MC_QUESTION must have options", node);
        return 0;
    }
    
    /* Count options and correct answers */
    for (int i = 0; i < options_node->num_children; i++) {
        ASTNode* option = options_node->children[i];
        if (option->type == NODE_OPTION) {
            option_count++;
            if (option->correct == 1) {
                correct_count++;
            }
        }
    }
    
    if (option_count < 2) {
        semantic_error("MC_QUESTION must have at least two options", node);
        valid = 0;
    }
    
    if (correct_count != 1) {
        semantic_error("MC_QUESTION must have exactly one correct option", node);
        valid = 0;
    }
    
    return valid;
}

int validate_tf_question(ASTNode* node) {
    int has_answer = 0;
    
    /* Check for ANSWER node */
    for (int i = 0; i < node->num_children; i++) {
        ASTNode* child = node->children[i];
        if (child->type == NODE_ANSWER) {
            has_answer = 1;
            break;
        }
    }
    
    if (!has_answer) {
        semantic_error("TF_QUESTION must have an ANSWER specified", node);
        return 0;
    }
    
    return 1;
}

int validate_if_score(ASTNode* node) {
    int valid = 1;
    
    /* Validate score threshold */
    if (node->score_value < 0) {
        semantic_error("IF_SCORE threshold must be non-negative", node);
        valid = 0;
    }
    
    /* Validate sections inside the IF_SCORE block */
    ASTNode* conditional_sections = NULL;
    if (node->num_children > 0) {
        conditional_sections = node->children[0];
    }
    
    if (!conditional_sections) {
        semantic_error("IF_SCORE block must contain sections", node);
        return 0;
    }
    
    /* Validate each section */
    int has_section = 0;
    for (int i = 0; i < conditional_sections->num_children; i++) {
        ASTNode* child = conditional_sections->children[i];
        if (child->type == NODE_SECTION) {
            has_section = 1;
            valid &= validate_section(child);
        }
    }
    
    if (!has_section) {
        semantic_error("IF_SCORE block must contain at least one section", node);
        valid = 0;
    }
    
    return valid;
}

void semantic_error(const char* message, ASTNode* node) {
    const char* node_type_str = "unknown";
    
    switch (node->type) {
        case NODE_ASSESSMENT: node_type_str = "ASSESSMENT"; break;
        case NODE_SECTIONS: node_type_str = "SECTIONS"; break;
        case NODE_SECTION: node_type_str = "SECTION"; break;
        case NODE_QUESTIONS: node_type_str = "QUESTIONS"; break;
        case NODE_MC_QUESTION: node_type_str = "MC_QUESTION"; break;
        case NODE_TF_QUESTION: node_type_str = "TF_QUESTION"; break;
        case NODE_OPTION: node_type_str = "OPTION"; break;
        case NODE_ANSWER: node_type_str = "ANSWER"; break;
        case NODE_FEEDBACK: node_type_str = "FEEDBACK"; break;
        case NODE_IF_SCORE: node_type_str = "IF_SCORE"; break;
    }
    
    printf("Semantic Error: %s (in %s \"%s\")\n", message, node_type_str, node->text);
}