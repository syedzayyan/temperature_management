<script>
    import TempPlot from "../../components/TempPlot.svelte";
    import { auth_state } from "../../stores/auth_state";
    import {
        Column,
        Grid,
        Loading,
        Row,
        Slider,
    } from "carbon-components-svelte";
    import { metatags } from "@roxi/routify";
    import { onMount } from "svelte";
    import { url } from "../../components/url";
    export let id;

    metatags.title = "Temperature for Freeze ID: " + id;
    let slideValue = 24;
    let maxTemp = 15;
    let minTemp = -30;
    let timeZoneOffset = 0;

    let auth_subbed_data;
    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });
    let corrAxisData;

    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${auth_subbed_data.token}`,
        },
    };
    onMount(async () => {
        setInterval(() => {
            fetch(`${url}/temperature/?id=${id}`, requestOptions)
                .then((res) => res.json())
                .then((data) => {
                    data.map((datum) => {
                        datum.reading_date = new Date(datum.reading_date + 'Z');
                    });
                    let axisData = JSON.stringify(data);
                    let round_1 = axisData
                        .replaceAll("temperature", "y")
                        .replaceAll("reading_date", "x");
                    corrAxisData = JSON.parse(round_1);
                });
        }, 30000);
    });
</script>

{#if corrAxisData}
    <div>
        <Grid fullWidth>
            <Row>
                <Column>
                    <Slider
                        labelText="Hours of data"
                        min={1}
                        max={24}
                        maxLabel="24 hrs"
                        bind:value={slideValue}
                    />
                </Column>
                <Column>
                    <Slider
                        labelText="Max Temperature Y-axis"
                        min={-100}
                        max={100}
                        bind:value={maxTemp}
                    />
                </Column>
                <Column>
                    <Slider
                        labelText="Min Temperature Y-axis"
                        min={-100}
                        max={100}
                        bind:value={minTemp}
                    />
                </Column>
                <Column>
                    <Slider
                        labelText="Time Zone Offset from UTC (GMT)"
                        min={-12}
                        max={12}
                        bind:value={timeZoneOffset}
                    />
                </Column>
            </Row>
            <TempPlot
                freezer_data={corrAxisData}
                {slideValue}
                {maxTemp}
                {minTemp}
                {timeZoneOffset}
            />
        </Grid>
    </div>
{:else}
    <h1>Loading could take up to 30 seconds</h1>
    <Loading description = "Loading could take up to 30 seconds"/>
{/if}
