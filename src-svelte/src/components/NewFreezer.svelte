<script>
    import { FluidForm, TextInput, Button } from "carbon-components-svelte";
    import { onMount } from "svelte";
    import { arduinolist } from "./arduinolist";
    import { auth_state } from "../stores/auth_state";
    import { url } from "./url"

    let arduino_data = [];
    onMount(async () => {
        arduino_data = await arduinolist();
    });

    let auth_subbed_data;
    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });
    let freezerName;
    let freezerMaxTemp = 30;
    let arduinoID;
    let created;

    const submitForm = async () => {
        const requestOptions = {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
            body: JSON.stringify({
                name: freezerName,
                arduino_id: arduinoID,
                max_temp: freezerMaxTemp
            }),
        };

        const response = await fetch(`${url}/freezer`, requestOptions);

        if (!response.ok) {
            alert("Problem");
        } else {
            window.location.reload()
        }
    };
</script>

<div>
    <h1>New Freezer {created}</h1>
    <FluidForm>
        <TextInput
            bind:value={freezerName}
            labelText="Name"
            placeholder="Name"
            required
        />
        <TextInput
            bind:value={freezerMaxTemp}
            placeholder="Max Temp"
        />
        <select bind:value={arduinoID}>
            <option disabled value="placeholder-item" text="Choose an option" />
            {#each arduino_data as item}
                <option value={item.id}>{item.arduinoname}</option>
            {/each}
        </select>
        <br />
        <Button on:click={submitForm}>Submit</Button>
    </FluidForm>
</div>
