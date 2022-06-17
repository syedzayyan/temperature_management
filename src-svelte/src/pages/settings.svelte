<script>
    import { metatags } from "@roxi/routify";
    import NewArduino from "../components/NewArduino.svelte";
    import NewFreezer from "../components/NewFreezer.svelte";
    import { Accordion, AccordionItem } from "carbon-components-svelte";
    import { auth_state } from "../stores/auth_state";
    import DeleteArduino from "../components/DeleteArduino.svelte";
import NewUser from "../components/NewUser.svelte";
import DeleteUser from "../components/DeleteUser.svelte";
import EditAdminUser from "../components/EditAdminUser.svelte";

    metatags.title = "Settings";

    let auth_subbed_data;
    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });
    
</script>

{#if auth_subbed_data.loggedIn}
    <div>
        
        <Accordion>
            {#if auth_subbed_data.admin}
            <AccordionItem title = "New User">
                <NewUser />
            </AccordionItem>
            <AccordionItem title = "Delete User">
                <DeleteUser />
            </AccordionItem>
            {/if}
            <AccordionItem title = "Edit User">
                <EditAdminUser />
            </AccordionItem>
            <AccordionItem title="New Arduino">
                <NewArduino />
            </AccordionItem>
            <AccordionItem title="New Freezer">
                <NewFreezer />
            </AccordionItem>
            <AccordionItem title="Delete">
                <DeleteArduino />
            </AccordionItem>
        </Accordion>
    </div>
{:else}
    <h1>Please Login In!</h1>
{/if}
