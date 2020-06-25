/* keeping token in memory */
let accessToken = ref(None);

let deleteAccessToken = () => accessToken := None;

let getAccessToken = () => accessToken^;

let setAccessToken = (token: string) => accessToken := Some(token);