#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* Main semantic analysis function */
int validate_semantics(ASTNode* root);

/* Individual validation functions */
int validate_assessment(ASTNode* node);
int validate_section(ASTNode* node);
int validate_mc_question(ASTNode* node);
int validate_tf_question(ASTNode* node);
int validate_if_score(ASTNode* node);

/* Helper function to print semantic errors */
void semantic_error(const char* message, ASTNode* node);

#endif /* SEMANTIC_H */