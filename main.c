

/** DO NOT MODIFY THIS FILE **/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "expression.h"

void processExpressions(const char *infile, const char *outfile);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s input.txt output.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    processExpressions(argv[1], argv[2]);
    return EXIT_SUCCESS;
}




void processExpressions(const char *infile, const char *outfile)
{
    FILE *in = fopen(infile, "r");
    FILE *out = fopen(outfile, "w");
    if (!in || !out)
    {
        fprintf(stderr, "Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[1000];
    char *tokens[MAX_EXPR];
    int count = 0;

    while (fscanf(in, "%s", buffer) == 1)
    {
        tokens[count] = strdup(buffer);
        count++;
    }

    Node *root = buildExpressionTree(tokens, count);

    // printInfix(root, out);
    int result = evaluate(root);
    fprintf(out,"%d", result);

    freeTree(root);
    for (int i = 0; i < count; i++)
        free(tokens[i]);

    fclose(in);
    fclose(out);
}