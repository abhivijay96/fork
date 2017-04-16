# fork call tree builder

<h2>Instructions to run:</h2><br/>
    compile fork.c<br/>
    <code>gcc fork.c -o fork.out </code><br/>
    Run the compiled code<br/>
    <code>./fork.out</code></br/>

<h2>How it works:</h2><br/>
    The c program asks the user the number of times it should fork. After every fork the parent waits for the child to complete using wait system call and whenever a leaf fork child completes execution all the nodes in that path from the parent resume execution from bottom up and write to the <code>output.txt</code> file in the format <code> PARENT parent_pid CHILD child_pid </code> this does not cause race condition because of the wait call.
    <br/>
    Then the python file <code> tree_generator.py </code> is invoked which parses data in <code>output.txt</code> and creates a dictionary where keys are pids of parents and value is list of pids of child processes, this list is then used to create a tree and the tree is dumped as a json object to <code>tree.json</code> file.

