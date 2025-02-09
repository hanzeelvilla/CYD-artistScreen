import dotenv from 'dotenv';
import axios from 'axios';

dotenv.config();

const args = process.argv;
const provideCode = args.length === 3 && !!args[2] == true;

if (!provideCode) {
    console.log('Code not provided');
    console.log('Usage: node index.js <code>');
    process.exit(1);
}

const code = args[2];

type spotifyToken = {
    refresh_token: string;
};

async function getSpotifyRefreshToken(code: string): Promise<spotifyToken> {
    const client_id: string = process.env.SPOTIFY_CLIENT_ID as string;
    const client_secret: string = process.env.SPOTIFY_CLIENT_SECRET as string;
    const redirect_uri = process.env.SPOTIFY_REDIRECT_URI as string;
    const params = new URLSearchParams();

    params.append('client_id', client_id);
    params.append('client_secret', client_secret);
    params.append('grant_type', 'authorization_code');
    params.append('code', code);
    params.append('redirect_uri', redirect_uri);

    const res = await axios({
        url: 'https://accounts.spotify.com/api/token',
        method: 'POST',
        params
    });

    return {refresh_token: res.data.refresh_token};
}

async function printRefreshToken() {
    try {
        const token = await getSpotifyRefreshToken(code);
        console.log('Your token is: ');
        console.log('');
        console.log(token);
        console.log('');
        console.log('Copy the token and save it in lib/spotifyControler/config.h');
    } catch (error) {
        console.error(error);
    }
}

printRefreshToken();