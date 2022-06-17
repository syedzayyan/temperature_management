<script>
    import { Select, SelectItem, Button } from "carbon-components-svelte";
    import { onMount } from "svelte";
    import { arduinolist } from "./arduinolist";
    import DeleteFreezer from "./DeleteFreezer.svelte";
    import { auth_state } from "../stores/auth_state";
    import TrashCan from "carbon-icons-svelte/lib/TrashCan.svelte";
    import { url } from "./url"

    
    let selected = 0;
    let arduino_data = [];
    let auth_subbed_data;

    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });
    onMount(async () => {
        arduino_data = await arduinolist();
    });
    async function submitForm() {
        const requestOptions = {
            method: "DELETE",
            headers: { 
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
        };

        const response = await fetch(
            `${url}/arduino/${selected}`,
            requestOptions
        );

        if (!response.ok) {
            alert("Problem");
        }
        window.location.reload();
    }
</script>

<div>
    <Select bind:selected labelText="Select Arduino to Delete or to reveal Freezers">
        <SelectItem value={0} text="Select an Arduino" disabled hidden />
        {#each arduino_data as item}
            <SelectItem value={item.id} text={item.arduinoname} />
        {/each}
    </Select>
    <Button kind="danger-tertiary" iconDescription="Delete" icon={TrashCan} on:click={submitForm}>Delete Arduino</Button>
    {#if selected != 0}
        <DeleteFreezer arduinoID = {selected}/>
    {/if}
</div>
