<script>
    export let freezer_data;
    export let slideValue;
    export let maxTemp;
    export let minTemp;
    export let timeZoneOffset;
    import "chartjs-adapter-luxon";
    import Line from "svelte-chartjs/src/Line.svelte";

    $: timeZoneOffsetFixer = () => {
        if (timeZoneOffset > -1){
            timeZoneOffset = "UTC+" + timeZoneOffset
        }else{
            timeZoneOffset = "UTC" + timeZoneOffset
        }
        return timeZoneOffset
    }

    $: data = {
        datasets: [
            {
                borderColor: "rgba(99,0,125, .2)",
                backgroundColor: "rgba(99,0,125, .5)",
                data: freezer_data,
                label: "Temperature (°C)",
            },
        ],
    };
    $: options = {
        plugins: {
            title: {
                display: true,
                text: 'Temperatures from the Freezer'
            },
            legend : {
                display: true,
            }
        },
        scales: {
            x: {
                type: "time",
                time: {
                    unit: "minute",
                },
                min: new Date(new Date(). getTime() - (slideValue * 60 * 60 * 1000)),
                max: new Date().getTime(),
                adapters: {
                    date: {
                        zone: timeZoneOffsetFixer(),
                    },
                },
                labels : "Dates"
            },
            y : {
                labels : "Temperature",
                min: minTemp,
                max: maxTemp,
            },
        },
    };
</script>
<div>
    <Line {data} {options} />
</div>

