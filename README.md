# fork call tree builder

<h2>Instructions to run:</h2><br/>
    compile fork.c<br/>
    <code>gcc fork.c -o fork.out </code><br/>
    Run the compiled code<br/>
    <code>./fork.out</code></br/>

<h2>How it works:</h2><br/>
    The c program asks the user the number of times it should fork. After every fork the parent waits for the child to complete using wait system call and whenever a leaf fork child completes execution all the nodes in that path from the parent resume execution from bottom up and write to the <span>output.txt</span> file in the format <span> PARENT parent_pid CHILD child_pid </span> this does not cause race condition because of the wait call.
    <br/>
    Then the python file <span> tree_generator.py </span> is invoked which parses data in <span>output.txt</span> and creates a dictionary where keys are pids of parents and value is list of pids of child processes, this list is then used to create a tree and the tree is dumped as a json object to <span>tree.json</span> file.

