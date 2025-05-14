pid_t
_user_fork(void)
{
    Thread* thread = thread_get_current_thread();
    Team* parentTeam = thread->team;
    
    // Create a new team (process)
    Team* newTeam = team_create_forked(parentTeam);
    if (newTeam == NULL)
        return B_NO_MEMORY;
    
    // Clone the address space
    status_t status = vm_copy_on_write(parentTeam->address_space,
                                      newTeam->address_space);
    if (status != B_OK) {
        team_delete(newTeam);
        return status;
    }
    
    // Clone file descriptors and other resources
    status = inherit_fd_table(parentTeam, newTeam);
    if (status != B_OK) {
        team_delete(newTeam);
        return status;
    }
    
    // Create the first thread in the new team
    Thread* newThread = thread_create_thread(newTeam);
    if (newThread == NULL) {
        team_delete(newTeam);
        return B_NO_MEMORY;
    }
    
    // Set up the thread's context to return 0 in child
    arch_fork_child(newThread);
    
    // Return the PID to parent
    return newTeam->id;
}
