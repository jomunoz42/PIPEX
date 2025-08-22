/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:53:50 by jomunoz           #+#    #+#             */
/*   Updated: 2025/08/22 19:54:04 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

                      
                            Valgrind Test Cases for Pipex

    Normal Command Execution

        ./pipex infile "cat" "cat" outfile

        Expect: No leaks, no fd errors, correct output.

    First Command Does Not Exist

        ./pipex infile "nonexistentcmd" "cat" outfile

        Expect: Bash-style "command not found" error, no leaks.

    Second Command Does Not Exist

        ./pipex infile "cat" "nonexistentcmd" outfile

        Expect: Bash-style "command not found" error, no leaks.

    Unreadable Infile

        Make infile without read permissions: chmod 000 infile

        Run: ./pipex infile "cat" "cat" outfile

        Expect: Bash-style permission denied error, no leaks.

    Unwritable Outfile

        Make outfile without write permissions: chmod 000 outfile

        Run: ./pipex infile "cat" "cat" outfile

        Expect: Bash-style permission denied error, no leaks.

    Missing Infile

        ./pipex doesnotexist "cat" "cat" outfile

        Expect: Error about missing file, no leaks.

    Multiple commands (bonus test)

        ./pipex infile "cat" "grep pattern" "wc -l" outfile

        Expect: Output from full chain, no leaks.

    Here_doc mode (bonus if implemented)

        ./pipex here_doc LIMITER "cat" "wc -l" outfile

        Test with various limiters and input, expect correct output, no leaks.

    Empty Input File

        Use an empty infile.

        Run: ./pipex infile "cat" "cat" outfile

        Expect: Outfile remains empty, no leaks.

    Large Input File

        Use a large file for infile.

        Run: ./pipex infile "cat" "cat" outfile

        Expect: Outfile matches infile, no leaks.

    Invalid Arguments

        Run with not enough args: ./pipex infile "cat"

        Run with too many: ./pipex infile "cat" "cat" "cat" outfile otherfile

        Expect: Argument error handling, no leaks.

    Pipe Creation Failure

        Artificially limit number of open files (advanced, ulimit -n <low value>) and force pipe creation to fail.

        Confirm handling and no leak.

    Fd Use After Close / Double Close

        Confirm code never writes to/reads from fds after closing; check for double-closing.

    Test with invalid file descriptors

        E.g., program tries to use -1 or an uninitialized fd; Valgrind should catch this.
