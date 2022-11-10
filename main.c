#include <stdio.h>

// Maximum string length
#define MAX 100

// String length
int my_strlen(char str[])
{
	// Length
	int len = 0;
	// While the symbol 0 is not found
	while (str[len] != '\0')
		// The length is increased by 1 character
		len++;
	// Return length
	return len;
}

// Converting a string to an integer
int my_stoi(char str[])
{
	// Result initialization
    int res = 0;
	// The length of a string
	int size = my_strlen(str);
	// Loop over all characters
    for (int i = 0; i < size; i++)
		// Adding to the number
        res = res * 10 + str[i] - '\0';
	// Returning a number
    return res;
}

// Compare strings for equality
int my_strcmp(char str1[], char str2[])
{
	// Calculating the length of the first string
	int size = my_strlen(str1);
	// If the lengths of the strings are not equal
	if (size != my_strlen(str2))
		// Strings are not equal
		return 0;
	// Loop over all characters
	for (int i = 0; i < size; i++)
		// If string characters are not equal
		if (str1[i] != str2[i])
			// Strings are not equal
			return 0;
	// Else strings are equal
	return 1;
}

// Check "character - lowercase letter"
int is_lower(char c)
{
	return ((c >= 'a') && (c <= 'z'));
}

// Check "character - uppercase letter"
int is_upper(char c)
{
	return ((c >= 'A') && (c <= 'Z'));
}

// Check "character - digit"
int is_digit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

// Check "character is a special character"
int is_spec(char c)
{
	return ((c >= 32) && (c <= 47)) || ((c >= 58) && (c <= 64))
		|| ((c >= 91) && (c <= 96)) || ((c >= 123) && (c <= 126));
}

// Rule 1
int rule1(char password[])
{
	// Calculating password length
	int size = my_strlen(password);
	// Flags for characters
	int low = 0, up = 0;
	// Loop over all characters
	for (int i = 0; i < size; i++)
	{
		// If no lowercase letter is found and the current character matches
		if (!low && is_lower(password[i]))
			// Change the flag of the lowercase letter to 1
			low = 1;
		// If no uppercase letter is found and the current character matches
		else if (!up && is_upper(password[i]))
			// Change the flag of the uppercase letter to 1
			up = 1;
		// If lowercase and uppercase letters are found
		if (low && up)
			// Password is ok for rule 1
			return 1;
	}
	// Password is not ok for rule 1
	return 0;
}

// Rule 2
int rule2(char password[], int X)
{
	// Calculating password length
	int size = my_strlen(password);
	// Flags for characters
	int low = 0, up = 0, dig = 0, spec = 0;
	// Loop over all characters
	for (int i = 0; i < size; i++)
	{
		// If no lowercase letter is found and the current character matches
		if (!low && is_lower(password[i]))
			// Change the flag of the lowercase letter to 1
			low = 1;
		// If no uppercase letter is found and the current character matches
		else if (!up && is_upper(password[i]))
			// Change the flag of the uppercase letter to 1
			up = 1;
		// If no digit is found and the current character matches
		else if (!dig && is_digit(password[i]))
			// Change the flag of the digit to 1
			dig = 1;
		// If the special character is not found and the current character matches
		else if (!spec && is_spec(password[i]))
			// Change the flag of the special character to 1
			spec = 1;
		// If the number of groups is not less than parameter X
		if (low + up + dig + spec >= X)
			// Password is ok for rule 2
			return 1;
	}
	// Password is not ok for rule 2
	return 0;
}

// Rule 3
int rule3(char password[], int X)
{
	// Calculating password length
	int size = my_strlen(password);
	// Start index
	int i = 0;
	// Until all characters have not been checked
	while (i < size)
	{
		// Get the current character and go to the next
		char c = password[i++];
		// The number of times a character is repeated is 1
		int count = 1;
		// Until all characters have been checked and the current character is repeated
		while (i < size && password[i++] == c)
			// The number of times a character is repeated increases by 1
			count++;
		// If the number of times a character is repeated  is not less than parameter X
		if (count >= X)
			// Password is not ok for rule 3
			return 0;
	}
	// Password is ok for rule 3
	return 1;
}

// Rule 4
int rule4(char password[], int X)
{
	// Calculating password length
	int size = my_strlen(password);
	// Loop over all substrings of length X except the last one
	for (int i = 0; i < size - X; i++)
		// Loop over all substrings of length X after the current one
		for (int j = i + 1; j < size - X + 1; j++)
		{
			// Substring match flag
			int found = 1;
			// Loop through substring characters
			for (int k = 0; k < X; k++)
			{
				// If the matching characters do not match
				if (password[i + k] != password[j + k])
				{
					// The flag changes to 0
					found = 0;
					// Exiting the loop
					break;
				}
			}
			// If the lines match
			if (found)
				// Password is not ok for rule 4
				return 0;
		}
	// Password is ok for rule 4
	return 1;
}

// Checking rules
int checkRule(char password[], int LEVEL, int PARAM)
{
	// Password validity flag (rule 1 is checked)
	int result = rule1(password);
	// If rule 1 is met and the following rules are required
	if (result && LEVEL >= 2)
	{
		// Check rule 2
		result *= rule2(password, PARAM);
		// If rule 2 is met and the following rules are required
		if (result && LEVEL >= 3)
		{
			// Check rule 3
			result *= rule3(password, PARAM);
			// If rule 3 is met and the rule 4 is required
			if (result && LEVEL >= 4)
				// Check rule 4
				result *= rule4(password, PARAM);
		}
	}
	// Output of the check result
	return result;
}

// Checking for a character in a string
int contains(char str[], char c)
{
	// Calculating password length
	int size = my_strlen(str);
	// Loop through all elements of a row
	for (int i = 0; i < size; i++)
		// If the symbol was found
		if (str[i] == c)
			return 1;
	// Otherwise, the symbol was not found.
	return 0;
}

// Adding new characters from the password
void addChars(char diffChars[], char password[])
{
	// Calculating the length of a string containing all distinct characters
	int diff_size = my_strlen(diffChars);
	// Calculating the length of a string
	int pass_size = my_strlen(password);
	// Loop through all characters except \0
	for (int i = 0; i < pass_size - 2; i++)
	{
		// If this is a new character
		if (!contains(diffChars, password[i]))
		{
			// The character is appended to the string-set
			diffChars[diff_size++] = password[i];
			diffChars[diff_size] = 0;
		}
	}
}

// The main code
int main(int argc, char* argv[])
{
	// The number of arguments checking
	if (argc < 3 || argc > 4)
	{
		// If the number of arguments incorrect (must be from 3 to 4 (0 - program name, 1 - LEVEL, 2 - Param, 3 - stats)
		printf("Incorrect number of parameters!\n");
		// Exit
		return 1;
	}

	// LEVEL
	int LEVEL = my_stoi(argv[1]);
	// Argument checking
	if (LEVEL < 1 || LEVEL > 4)
	{
		// If Level is incorrect (must be from 1 to 4)
		printf("LEVEL must be a number [1, 4]!\n");
		// Exit
		return 1;
	}

	// PARAM
	int PARAM = my_stoi(argv[2]);
	// Argument checking
	if (PARAM <= 0)
	{
		// If PARAM is
		printf("PARAM must be a positive number!\n");
		// Exit
		return 1;
	}

	// --stats
	if (argc == 4 && !my_strcmp(argv[3], "--stats"))
	{
		// If the third parameter does not match (not equal to --stats)
		printf("Third parameter must be --stats\n");
		// Exit
		return 1;
	}

	// Total password length
	double sum_len = 0.0;
	// Number of passwords and minimum password length
	int pass_count = 0, min_len = MAX + 1;
	// String storing various characters
	char diffChars[MAX];
	diffChars[0] = 0;

	// While entering passwords continues
	while (1)
	{
		// Password
		char password[MAX];
		// If the password is read
		if (fgets(password, MAX, stdin))
		{
			// Getting password length
			int len = my_strlen(password);
			// If the password is too long
			if (password[len - 1] != 10)
				// It is discarded
				continue;

			// Exclude characters # 10, # 13
			len -= 2;
			// If the password matches the rules
			if (checkRule(password, LEVEL, PARAM))
				// Password is displayed
				printf("%s", password);
			// The length is added to the total length
			sum_len += len;
			// If the length is less than the minimum
			if (len < min_len)
				// Changing the minimum length
				min_len = len;
			// Increase the number of passwords by 1
			pass_count++;
			// Adding password characters
			addChars(diffChars, password);
		}
		// Otherwise, exit the loop
		else
			break;
	}

	// If you need to display statistics
	if (argc == 4)
	{
		printf("Statistika\n");
		// Displaying the number of different characters
		printf("Ruznych znaku: %d\n", my_strlen(diffChars));
		// Minimum password length
		printf("Minimalni delka: %d\n", min_len);
		// Average password length
		printf("Prumerna delka: %.1f\n", sum_len / pass_count);
	}

	// Exit
	return 0;
}
